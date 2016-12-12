
local select = select
local unpack = unpack

local oo        = require "oil.oo"
local giop      = require "oil.corba.giop"
local Requester = require "oil.corba.giop.Requester"                            --[[VERBOSE]] local verbose = require "oil.verbose"

module "oil.corba.intercepted.Requester"

oo.class(_M, Requester)

--------------------------------------------------------------------------------

local RequestID = giop.RequestID

local Empty = {}

--------------------------------------------------------------------------------

function interceptrequest(self, reference, operation, request)
	local interceptor = self.interceptor
	if interceptor then
		local interface = operation.defined_in
		local intercepted = {
			reference         = reference,
			operation         = operation,
			profile_tag       = reference._profiletag,
			profile_data      = reference._profiledata,
			interface         = interface,
			interface_name    = interface and interface.absolute_name,
			request_id        = request.request_id,
			response_expected = request.response_expected,
			object_key        = request.object_key,
			operation_name    = request.operation,
			parameters        = { n = request.n, unpack(request, 1, request.n) },
		}
		request.intercepted = intercepted
		if interceptor.sendrequest then                                             --[[VERBOSE]] verbose:interceptors(true, "intercepting request being sent")
			interceptor:sendrequest(intercepted)
			if intercepted.success ~= nil then                                        --[[VERBOSE]] verbose:interceptors("interception request was canceled")
				request.success = intercepted.success
				-- update returned values
				local results = intercepted.results or {}
				request.n = results.n or #results
				for i = 1, request.n do
					request[i] = results[i]
				end
			else
				-- update parameter values
				local parameters = intercepted.parameters
				request.n = parameters.n or #parameters
				for i = 1, request.n do
					request[i] = parameters[i]
				end
				-- update operation being invoked
				if intercepted.operation and intercepted.operation ~= operation then
					operation = intercepted.operation
					interface = operation.defined_in
					intercepted.interface      = interface
					intercepted.interface_name = interface and interface.absolute_name
					intercepted.operation_name = operation.name
					request.operation  = operation.name
					request.inputs     = operation.inputs
					request.outputs    = operation.outputs
					request.exceptions = operation.exceptions
				end
				-- update GIOP message fields
				request.object_key           = intercepted.object_key
				request.response_expected    = intercepted.response_expected
				request.service_context      = intercepted.service_context or
				                               request.service_context
				request.requesting_principal = intercepted.requesting_principal or
				                               request.requesting_principal             --[[VERBOSE]] verbose:interceptors(false, "interception ended")
			end
		end
		return intercepted
	end
end

function sendrequest(self, reference, operation, ...)
	local result, except = self:getchannel(reference)
	local channel = result
	local request = self:makerequest(channel, reference._objectkey, operation,...)--[[VERBOSE]] verbose:invoke(true, "request ",request.request_id," for operation '",operation.name,"'")
	local intercepted = self:interceptrequest(reference, operation, request)
	if intercepted then
		if request.success ~= nil then                                              --[[VERBOSE]] verbose:interceptors(false, "interception ended (results provided!)")
			channel = nil
			result = request
		else
			local reference = intercepted.forward_reference
			if reference then                                                           --[[VERBOSE]] verbose:interceptors("intercepted request forwarded")
				if request.channel then
					unregister(request.channel, request.request_id)
				end
				result, except = self:getchannel(reference)
				if result then
					intercepted.object_key = reference._objectkey
					intercepted.profile_tag = reference._profiletag
					intercepted.profile_data = reference._profiledata
					channel = result
					request.object_key = except
					if request.response_expected then
						register(channel, request)
					else
						request.request_id = 0
					end
				else
					channel = nil
				end
			elseif not request.response_expected and request.channel then               --[[VERBOSE]] verbose:interceptors("interception canceled expected response")
				unregister(request.channel, request.request_id)
				request.request_id = 0
			elseif request.response_expected and not request.channel and channel then   --[[VERBOSE]] verbose:interceptors("interception asked for an expected response")
				register(channel, request)
			end
			intercepted.request_id = request.request_id
		end
	end
	if channel then
		result, except = self:sendmsg(channel, RequestID, request,
		                              request.inputs, request)
		if result then
			if not request.response_expected then
				request.success = true
				request.n = 0
			end
			result, except = request, nil
		else
			unregister(channel, request.request_id)
		end
	end
	if not result then
		request.success = false
		request.n = 1
		request[1] = except
		result, except = request, nil
	end                                                                           --[[VERBOSE]] verbose:invoke(false)
	if result and result.success ~= nil then
		result.service_context = nil
		self:interceptreply(result, result)
	end
	return result, except
end

--------------------------------------------------------------------------------

function interceptreply(self, request, header)
	local intercepted = request.intercepted
	if intercepted then
		request.intercepted = nil
		local interceptor = self.interceptor
		if interceptor and interceptor.receivereply then
			if header.service_context then
				intercepted.reply_service_context = header.service_context
			end
			intercepted.reply_status          = header.reply_status
			intercepted.success               = request.success
			intercepted.results = {
				n = request.n,
				unpack(request, 1, request.n),
			}
			interceptor:receivereply(intercepted)
			request.success = intercepted.success
			-- update returned values
			local results = intercepted.results or {}
			request.n = results.n or #results
			for i = 1, request.n do
				request[i] = results[i]
			end
		end
	end
end

function doreply(self, request, header, decoder)
	local success, except = Requester.doreply(self, request, header, decoder)
	if success then
		self:interceptreply(request, header)
	end
	return success, except
end
