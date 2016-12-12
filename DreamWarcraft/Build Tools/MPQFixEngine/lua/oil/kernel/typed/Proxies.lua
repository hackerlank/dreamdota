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
-- indexer:Facet
-- 	interface:table typeof(reference:table)
-- 	member:table, [islocal:function], [cached:boolean] valueof(interface:table, name:string)
--
-- invoker:Receptacle
-- 	[results:object], [except:table] invoke(reference, operation, args...)
--------------------------------------------------------------------------------

local rawset = rawset

local tabop       = require "loop.table"                                        --[[VERBOSE]] local select = select
local ObjectCache = require "loop.collection.ObjectCache"                       --[[VERBOSE]] local type   = type

local oo        = require "oil.oo"
local Exception = require "oil.Exception"
local Proxies   = require "oil.kernel.base.Proxies"                             --[[VERBOSE]] local verbose = require "oil.verbose"

module "oil.kernel.typed.Proxies"

oo.class(_M, Proxies)

--------------------------------------------------------------------------------

local function newclass(methodmaker)
	return oo.class{
		__call = oo.rawnew,
		__index = function(cache, field)                                            --[[VERBOSE]] verbose:proxies("first attempt to invoke operation ",field)
			local manager = cache.__manager
			local operation = manager.indexer:valueof(cache.__type, field)
			if operation then
				local function invoker(self, ...)                                       --[[VERBOSE]] verbose:proxies("call to ",operation, ...)
					return manager.requester:newrequest(self.__reference, operation, ...)
				end
				invoker = methodmaker(invoker, operation)                               --[[VERBOSE]] verbose:proxies("operation named ",field," was created")
				cache[field] = invoker                                                  --[[VERBOSE]]
				return invoker                                                          --[[VERBOSE]] else verbose:proxies("operation named ",field," not found")
			end
		end
	}
end

--------------------------------------------------------------------------------

function proxynarrow(self, type)
	return self.__manager.proxies:newproxy(self.__reference, type)
end

function __init(self, ...)
	self = oo.rawnew(self, ...)
	self.class = self.class or newclass(self.invoker)
	self.classes = ObjectCache{
		retrieve = function(_, type)
			local class = self.class()
			local updater = {}
			function updater.notify()
				tabop.clear(class)
				class.__manager = self
				class.__type = type
				class.__tostring = proxytostring
				class.__narrow = proxynarrow
				class._narrow = proxynarrow -- TODO:[maia] DEPRECATED!
				oo.initclass(class)
			end
			updater:notify()
			if type.observer then
				rawset(type.observer, class, updater)
			end
			return class
		end
	}
	return self
end

--------------------------------------------------------------------------------

function newproxy(self, reference, type)                                        --[[VERBOSE]] verbose:proxies(true, "new proxy to ",reference," with type ",type)
	local result, except
	if not type then                                                              --[[VERBOSE]] verbose:proxies(true, "interface of proxy not provided, attempt to discover it")
		type, except = self.referrer:typeof(reference)                              --[[VERBOSE]] verbose:proxies(false, "interface of proxy",(type and " " or " not "),"found")
	end
	if type then
		type, except = self.types:resolve(type)
		if type then
			result = self.classes[type]{ __reference = reference }
		end
	end                                                                           --[[VERBOSE]] verbose:proxies(false)
	return result, except
end

function excepthandler(self, handler, type)                                     --[[VERBOSE]] verbose:proxies("setting exception handler for proxies of ",type)
	local result, except = true
	if type == nil then
		result, except = Proxies.excepthandler(self, handler)
	else
		result, except = self.types:resolve(type)
		if result then
			type = result
			local class = self.classes[type]
			class.__exceptions = handler
			result, except = class, nil
		end
	end
	return result, except
end

--------------------------------------------------------------------------------

--[[VERBOSE]] function verbose.custom:proxies(...)
--[[VERBOSE]] 	local params
--[[VERBOSE]] 	for i = 1, select("#", ...) do
--[[VERBOSE]] 		local value = select(i, ...)
--[[VERBOSE]] 		local type = type(value)
--[[VERBOSE]] 		if type == "string" then
--[[VERBOSE]] 			if params then
--[[VERBOSE]] 				self.viewer.output:write(params)
--[[VERBOSE]] 				params = ", "
--[[VERBOSE]] 				self.viewer:write((value:gsub("[^%w%p%s]", "?")))
--[[VERBOSE]] 			else
--[[VERBOSE]] 				self.viewer.output:write(value)
--[[VERBOSE]] 			end
--[[VERBOSE]] 		elseif not params and type == "table" and
--[[VERBOSE]] 		       value._type == "operation" then
--[[VERBOSE]] 			params = "("
--[[VERBOSE]] 			self.viewer.output:write(value.name)
--[[VERBOSE]] 		else
--[[VERBOSE]] 			if params then
--[[VERBOSE]] 				self.viewer.output:write(params)
--[[VERBOSE]] 				params = ", "
--[[VERBOSE]] 			end
--[[VERBOSE]] 			self.viewer:write(value)
--[[VERBOSE]] 		end
--[[VERBOSE]] 	end
--[[VERBOSE]] 	if params then
--[[VERBOSE]] 		self.viewer.output:write(params == "(" and "()" or ")")
--[[VERBOSE]] 	end
--[[VERBOSE]] end
