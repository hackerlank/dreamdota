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
-- Title  : Object Request Dispatcher                                         --
-- Authors: Renato Maia <maia@inf.puc-rio.br>                                 --
--------------------------------------------------------------------------------
-- dispatcher:Facet
-- 	success:boolean, [except:table]|results... dispatch(key:string, operation:string|function, params...)
--------------------------------------------------------------------------------

local luapcall     = pcall
local setmetatable = setmetatable
local type         = type
local select       = select
local unpack       = unpack

local table       = require "loop.table"
local oo          = require "oil.oo"
local Exception   = require "oil.Exception"                                     --[[VERBOSE]] local verbose = require "oil.verbose"

module("oil.kernel.base.Dispatcher", oo.class)

pcall = luapcall

context = false

--------------------------------------------------------------------------------
-- Dispatcher facet

function dispatch(self, request)
	local object, operation = request:preinvoke()
	if object then
		object = self.context.servants:retrieve(object)
		if object then
			local method = object[operation]
			if method then                                                            --[[VERBOSE]] verbose:dispatcher("dispatching operation ",object,":",operation,request:params())
				request:results(self.pcall(method, object, request:params()))
			else                                                                      --[[VERBOSE]] verbose:dispatcher("missing implementation of ",opname)
				request:results(false, Exception{
					reason = "noimplement",
					message = "no implementation for operation of object with key",
					operation = operation,
					object = object,
					key = key,
				})
			end
		else                                                                        --[[VERBOSE]] verbose:dispatcher("got illegal object ",key)
			request:results(false, Exception{
				reason = "badkey",
				message = "no object with key",
				key = key,
			})
		end
	end
end

--------------------------------------------------------------------------------

--[[VERBOSE]] function verbose.custom:dispatcher(...)
--[[VERBOSE]] 	local params
--[[VERBOSE]] 	for i = 1, select("#", ...) do
--[[VERBOSE]] 		local value = select(i, ...)
--[[VERBOSE]] 		local type = type(value)
--[[VERBOSE]] 		if params == true then
--[[VERBOSE]] 			params = "("
--[[VERBOSE]] 			if type == "string" then
--[[VERBOSE]] 				self.viewer.output:write(value)
--[[VERBOSE]] 			else
--[[VERBOSE]] 				self.viewer:write(value)
--[[VERBOSE]] 			end
--[[VERBOSE]] 		elseif type == "string" then
--[[VERBOSE]] 			if params then
--[[VERBOSE]] 				self.viewer.output:write(params)
--[[VERBOSE]] 				params = ", "
--[[VERBOSE]] 				self.viewer:write((value:gsub("[^%w%p%s]", "?")))
--[[VERBOSE]] 			else
--[[VERBOSE]] 				self.viewer.output:write(value)
--[[VERBOSE]] 				if value == ":" then params = true end
--[[VERBOSE]] 			end
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
