local error        = error
local getmetatable = getmetatable
local rawget       = rawget
local unpack       = unpack                                                     --[[VERBOSE]] local verbose = require "oil.verbose"

module "oil.kernel.base.Proxies.utils"

function proxytostring(self)
	return self.__manager.referrer:encode(self.__reference)
end

function unpackrequest(request)
	return request.success, unpack(request, 1, request.n)
end

function callhandler(self, ...)
	local handler = rawget(self, "__exceptions") or
	                rawget(getmetatable(self), "__exceptions") or
	                self.__manager.proxies.defaulthandler or
	                error((...))
	return handler(self, ...)
end

function assertresults(self, operation, success, except, ...)
	if not success then
		return callhandler(self, except, operation)
	end
	return except, ...
end
