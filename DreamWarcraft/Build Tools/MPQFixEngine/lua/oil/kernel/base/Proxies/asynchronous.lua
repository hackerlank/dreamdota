local oo    = require "oil.oo"                                                     --[[VERBOSE]] local verbose = require "oil.verbose"
local utils = require "oil.kernel.base.Proxies.utils"

local assertresults = utils.assertresults
local unpackrequest = utils.unpackrequest

--------------------------------------------------------------------------------

local Request = oo.class()

function Request:ready()                                                        --[[VERBOSE]] verbose:proxies("check reply availability")
	local proxy = self.proxy
	assertresults(proxy, self.member,
	              proxy.__manager.requester:getreply(self, true))
	return self.success ~= nil
end

function Request:results()                                                      --[[VERBOSE]] verbose:proxies(true, "get reply results")
	local success, except = self.proxy.__manager.requester:getreply(self)
	if success then                                                               --[[VERBOSE]] verbose:proxies(false, "got results successfully")
		return unpackrequest(self)
	end                                                                           --[[VERBOSE]] verbose:proxies(false, "got errors while reading reply")
	return success, except
end

function Request:evaluate()                                                     --[[VERBOSE]] verbose:proxies("get deferred results of ",self.member)
	return assertresults(self.proxy, self.member, self:results())
end

--------------------------------------------------------------------------------

local Failed = oo.class({}, Request)

function Failed:ready()
	return true
end

function Failed:results()
	return false, self[1]
end

--------------------------------------------------------------------------------

return function(invoker, operation)
	return function(self, ...)
		local request, except = invoker(self, ...)
		if request then
			request = Request(request)
		else
			request = Failed{ except }
		end
		request.proxy = self
		request.member = operation
		return request
	end
end
