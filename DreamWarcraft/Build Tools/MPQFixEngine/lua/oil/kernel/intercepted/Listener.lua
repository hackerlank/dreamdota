
local unpack = unpack

local Wrapper = require "loop.object.Wrapper"

local oo = require "oil.oo"                                                     --[[VERBOSE]] local verbose = require "oil.verbose"

module("oil.kernel.intercepted.Listener", oo.class)

__init = Wrapper.__init
__index = Wrapper.__index

function getrequest(self, channel, probe)
	local result, except = self.__object:getrequest(channel, probe)
	if result then                                                                --[[VERBOSE]] verbose:interceptors(true, "intercepting request being sent")
		local request = {
			target    = result.objectkey,
			operation = result.operation,
			n         = result.n,
			unpack(result, 1, result.n),
		}
		local interceptor = self.interceptor
		if interceptor.getrequest then
			interceptor:getrequest(request)                                           --[[VERBOSE]] verbose:interceptors(false, "interception ended")
			if request.success ~= nil then                                            --[[VERBOSE]] verbose:interceptors("interception canceled request")
				result, except = self.__object:sendreply(request)
				if result then
					return self:getrequest(channel, probe)
				end
			end
		end
		result[self] = request
	end
	return result, except
end

function sendreply(self, reply)
	local request = reply[self]
	if request then
		replt[self] = nil
		local interceptor = self.interceptor
		if interceptor.sendreply then                                               --[[VERBOSE]] verbose:interceptors(true, "intercepting received reply")
			interceptor:sendreply(reply, request)                                     --[[VERBOSE]] verbose:interceptors(false, "interception ended")
		end
	end
	return self.__object:sendreply(reply)
end
