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
-- 	success:boolean, [except:table]|results... dispatch(objectkey:string, operation:string|function, params...)
-- 
-- indexer:Receptacle
-- 	[member:string], [implementation:function] valueof(objectkey:string, operation:string)
--------------------------------------------------------------------------------

local unpack = unpack

local oo         = require "oil.oo"
local Exception  = require "oil.Exception"
local Dispatcher = require "oil.kernel.base.Dispatcher"                         --[[VERBOSE]] local verbose = require "oil.verbose"

module "oil.kernel.typed.Dispatcher"

oo.class(_M, Dispatcher)

context = false

--------------------------------------------------------------------------------
-- Dispatcher facet

function dispatch(self, request)
	local context = self.context
	local servants = context.servants
	local key = request.object_key
	local opname = request.operation
	local opinfo
	local object, type = servants:retrieve(key)
	if object == nil then                                                         --[[VERBOSE]] verbose:dispatcher("got illegal object ",key)
		request:results(false, Exception{
			reason = "badkey",
			message = "no object with key",
			key = key,
		})
	else
		opinfo = context.indexer:valueof(type, opname)
		if opinfo == nil then                                                         --[[VERBOSE]] verbose:dispatcher("got illegal operation ",opname)
			request:results(false, Exception{
				reason = "badoperation",
				message = "operation is illegal for object with key",
				operation = opname,
				object = object,
				type = type,
				key = key,
			})
		end
	end
	key, opname = request:preinvoke(type, opinfo, object)
	if key == nil then                                                            --[[VERBOSE]] verbose:dispatcher("pre-invocation failed!")
		return -- cancel dispatch
	end
	if key ~= request.objectkey then
		object = servants:retrieve(key)
		if object == nil then                                                       --[[VERBOSE]] verbose:dispatcher("got illegal object ",key)
			request:results(false, Exception{
				reason = "badkey",
				message = "no object with key",
				key = key,
			})
			return -- cancel dispatch
		end
	end
	local method = object[opname] or opinfo.implementation
	if method == nil then                                                         --[[VERBOSE]] verbose:dispatcher("missing implementation of ",opname)
		return request:results(false, Exception{
			reason = "noimplement",
			message = "no implementation for operation of object with key",
			operationdescription = opinfo,
			operation = opname,
			object = object,
			type = type,
			key = key,
		})
	end                                                                           --[[VERBOSE]] verbose:dispatcher("dispatching operation ",key,":",opname,request:params())
	request:results(self.pcall(method, object, request:params()))
end
