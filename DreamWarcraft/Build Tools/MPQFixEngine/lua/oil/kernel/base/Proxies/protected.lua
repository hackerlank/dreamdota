local utils = require "oil.kernel.base.Proxies.utils"

local unpackrequest = utils.unpackrequest

return function(invoker)
	return function(self, ...)
		local success, except = invoker(self, ...)
		if success then
			local request = success
			success, except = self.__manager.requester:getreply(request)
			if success then
				return unpackrequest(request)
			end
		end
		return success, except
	end
end
