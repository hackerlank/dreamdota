local utils = require "oil.kernel.base.Proxies.utils"

local assertresults = utils.assertresults
local unpackrequest = utils.unpackrequest
local callhandler   = utils.callhandler

return function(invoker, operation)
	return function(self, ...)
		local request, except = invoker(self, ...)
		if request then
			assertresults(self, operation, self.__manager.requester:getreply(request))
			return assertresults(self, operation, unpackrequest(request))
		else
			return callhandler(self, except, operation)
		end
	end
end
