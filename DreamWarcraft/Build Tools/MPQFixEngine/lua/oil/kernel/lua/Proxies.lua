--------------------------------------------------------------------------------
------------------------------  #####      ##     ------------------------------
------------------------------ ##   ##  #  ##     ------------------------------
------------------------------ ##   ## ##  ##     ------------------------------
------------------------------ ##   ##  #  ##     ------------------------------
------------------------------  #####  ### ###### ------------------------------
--------------------------------                --------------------------------
----------------------- An Object Request Broker in Lua ------------------------
--------------------------------------------------------------------------------
-- Project: OiL - ORB in Lua: An Object Request Broker in Lua                 --
-- Release: 0.5                                                               --
-- Title  : Remote Object Proxies                                             --
-- Authors: Renato Maia <maia@inf.puc-rio.br>                                 --
--------------------------------------------------------------------------------
-- proxies:Facet
-- 	proxy:object proxyto(reference:table)
--
-- invoker:Receptacle
-- 	[results:object], [except:table] invoke(reference, operation, args...)
--------------------------------------------------------------------------------

local ipairs = ipairs

local oo      = require "oil.oo"
local Proxies = require "oil.kernel.base.Proxies"                               --[[VERBOSE]] local verbose = require "oil.verbose"
local utils   = require "oil.kernel.base.Proxies.utils"

module "oil.kernel.lua.Proxies"

oo.class(_M, Proxies)

local assertresults = utils.assertresults
local unpackrequest = utils.unpackrequest
local callhandler   = utils.callhandler

class = oo.class()
for _, field in ipairs{
	"tostring",
	"unm",
	"len",
	"add",
	"sub",
	"mul",
	"div",
	"mod",
	"pow",
	"eq",
	"lt",
	"le",
	"concat",
	"call",
	"index",
	"newindex",
} do
	class["__"..field] = function(self, ...)                                      --[[VERBOSE]] verbose:proxies("call to ",field," ", ...)
		local requester = self.__manager.requester
		local success, except = requester:newrequest(self.__reference, field, ...)
		if success then
			local request = success
			success, except = requester:getreply(request)
			if success then
				return assertresults(self, operation, unpackrequest(request))
			end
		end
		if not success then
			return callhandler(self, except, operation)
		end
	end
end
