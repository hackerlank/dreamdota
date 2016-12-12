
local unpack = unpack

local oo       = require "oil.oo"
local giop     = require "oil.corba.giop"
local Listener = require "oil.corba.giop.Listener"                              --[[VERBOSE]] local verbose = require "oil.verbose"

module "oil.corba.intercepted.Listener"

oo.class(_M, Listener)

--------------------------------------------------------------------------------

local LocationForwardTypes = { giop.IOR }
local ReplyID = giop.ReplyID

local Empty = {}

--------------------------------------------------------------------------------

function __init(self, ...)
	self = oo.rawnew(self, ...)
	local Request = self.Request
	self.Request = oo.class({}, Request)
	function self.Request.preinvoke(request, iface, member, object)
		local objkey, opname = Request.preinvoke(request, iface, member)
		request.interface = iface
		request.member = member
		request.target = object
		self:interceptrequest(request, objkey == nil)
		if request.success == nil then
			return objkey, opname
		end
	end
	return self
end

--------------------------------------------------------------------------------

function interceptrequest(self, request, failed)
	local interceptor = self.interceptor
	if interceptor then
		local intercepted = {
			service_context   = request.service_context,
			request_id        = request.request_id,
			response_expected = request.response_expected,
			object_key        = request.object_key,
			operation_name    = request.operation,
			servant           = request.target,
			interface         = request.interface,
			interface_name    = request.interface and request.interface.absolute_name,
			operation         = request.member,
			parameters        = not failed and {n=request.n,request:params()} or nil,
		}
		request.intercepted = intercepted
		if interceptor.receiverequest then                                          --[[VERBOSE]] verbose:interceptors(true, "intercepting request marshaling")
			interceptor:receiverequest(intercepted)
			if intercepted.success ~= nil then                                        --[[VERBOSE]] verbose:interceptors("interception request was canceled")
				request.success = intercepted.success
				-- update returned values
				local results = intercepted.results or {}
				request.n = results.n or #results
				for i = 1, request.n do
					request[i] = results[i]
				end
				request.intercepted = nil -- this should cancel the reply interception
				request.reply_service_context = intercepted.reply_service_context
			elseif intercepted.forward_reference then                                 --[[VERBOSE]] verbose:interceptors("interceptor forwarded the request")
				request.success = false   -- this should cancel the operation dispatch
				request.intercepted = nil -- this should cancel the reply interception
				request.reply_service_context = intercepted.reply_service_context
				request.forward_reference = intercepted.forward_reference
			else
				-- update parameter values
				local parameters = intercepted.parameters
				if parameters then
					request.n = parameters.n or #parameters
					for i = 1, request.n do
						request[i] = parameters[i]
					end
				end
				-- update operation being invoked
				if intercepted.operation ~= request.member then                         --[[VERBOSE]] verbose:interceptors("interceptor changed invoked operation")
					local operation = intercepted.operation
					request.operation  = operation.name
					request.inputs     = operation.inputs
					request.outputs    = operation.outputs
					request.exceptions = operation.exceptions
				end
				-- update GIOP message fields
				request.service_context = intercepted.service_context
				request.object_key = intercepted.object_key
			end                                                                       --[[VERBOSE]] verbose:interceptors(false, "interception ended")
		end
	end
end

--------------------------------------------------------------------------------

function interceptreply(self, request, body)
	local intercepted = request.intercepted
	if intercepted then
		request.intercepted = nil
		local interceptor = self.interceptor
		if interceptor and interceptor.sendreply then
			intercepted.reply_status = request.reply_status
			intercepted.success      = request.success
			if request.reply_status == "SYSTEM_EXCEPTION" then
				intercepted.results = { n = 1, body[1] }
			else
				intercepted.results = { n = request.n, unpack(request, 1, request.n) }
			end                                                                       --[[VERBOSE]] verbose:interceptors(true, "intercepting reply marshaling")
			interceptor:sendreply(intercepted)                                        --[[VERBOSE]] verbose:interceptors(false, "interception ended")
			local reference = intercepted.forward_reference
			if reference then
				request.forward_reference = reference
			else
				request.success = intercepted.success
				-- update returned values
				local results = intercepted.results or {}
				request.n = results.n or #results
				for i = 1, request.n do
					request[i] = results[i]
				end
			end
			-- update GIOP message fields
			request.reply_service_context = intercepted.reply_service_context
			return true
		end
	end
end

function makereply(self, request)
	local types, body
	local reference = request.forward_reference
	if reference then
		request.reply_status = "LOCATION_FORWARD"
		request.service_context = Empty
		return LocationForwardTypes, { reference }
	end
	local header, types, body = Listener.handlereply(self, request)
	if header ~= request then
		request.reply_status    = header.reply_status
		request.service_context = header.service_context
	end
	return types, body
end

function handlereply(self, request)
	local types, body = self:makereply(request)
	if self:interceptreply(request, body) then
		types, body = self:makereply(request)
		if request.reply_service_context then
			request.service_context = request.reply_service_context
		end
	end
	return request, types, body
end
