
local select = select
local unpack = unpack

local Wrapper = require "loop.object.Wrapper"

local oo = require "oil.oo"                                                     --[[VERBOSE]] local verbose = require "oil.verbose"

module("oil.kernel.intercepted.Requester", oo.class)

__init = Wrapper.__init
__index = Wrapper.__index

function newrequest(self, reference, operation, ...)
	local request = {
		reference = reference,
		operation = operation,
		n = select("#", ...),
		...,
	}
	local result, except
	local interceptor = self.interceptor
	if interceptor.newrequest then                                                --[[VERBOSE]] verbose:interceptors(true, "intercepting request being sent")
		interceptor:newrequest(request)                                             --[[VERBOSE]] verbose:interceptors(false, "interception ended")
		if request.success ~= nil then                                              --[[VERBOSE]] verbose:interceptors("interception canceled request")
			result, except = request, nil
		else
			result, except = self.__object:newrequest(request.reference,
			                                          request.operation,
			                                          unpack(request, 1, request.n))
		end
	else
		result, except = self.__object:newrequest(reference, operation, ...)
	end
	if not result then
		request.success = false
		request.n = 1
		request[1] = except
		result, except = request, nil
	end
	result[self] = request
	return result, except
end

function getreply(self, opreq)
	local result, except = self.__object:getreply(opreq)
	if result then
		local interceptor = self.interceptor
		local request = opreq[self]
		if request then
			opreq[self] = nil
			if interceptor.getreply then                                              --[[VERBOSE]] verbose:interceptors(true, "intercepting received reply")
				interceptor:getreply(request, opreq)                                    --[[VERBOSE]] verbose:interceptors(false, "interception ended")
			end
		end
	end
	return result, except
end
