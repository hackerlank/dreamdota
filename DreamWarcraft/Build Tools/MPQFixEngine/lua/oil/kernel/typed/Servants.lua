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
-- Title  : Server-Side Broker                                                --
-- Authors: Renato Maia <maia@inf.puc-rio.br>                                 --
--------------------------------------------------------------------------------
-- broker:Facet
-- 	servant:object register(impl:object, [objectkey:string])
-- 	impl:object remove(servant:object|impl:object|objectkey:string)
-- 	impl:object retrieve(objectkey:string)
-- 	reference:string tostring(servant:object)
--
-- referrer:Receptacle
-- 	reference:table newreference(objectkey:string, accesspointinfo:table...)
-- 	stringfiedref:string encode(reference:table)
-- 
-- types:Receptacle
-- 	type:table resolve(type:string)
--------------------------------------------------------------------------------

local getmetatable = getmetatable
local rawget       = rawget
local type         = type

local table = require "loop.table"

local oo       = require "oil.oo"
local Servants = require "oil.kernel.base.Servants"                             --[[VERBOSE]] local verbose = require "oil.verbose"

module "oil.kernel.typed.Servants"

oo.class(_M, Servants)

--------------------------------------------------------------------------------
--------------------------------------------------------------------------------

function addentry(self, key, impl, type)
	local entry = self.map[key]
	if entry == nil
	or entry.object ~= impl
	or entry.type ~= type
	then
		return Servants.addentry(self, key, { object = impl, type = type })
	end
	return true
end

function removeentry(self, key)
	local result, except = Servants.removeentry(self, key)
	if result then result, except = result.object, result.type end
	return result, except
end

--------------------------------------------------------------------------------
--------------------------------------------------------------------------------

function resolvetype(self, object)
	local objtype = nil
	local meta = getmetatable(object)
	if type(object) == "table" or (meta ~= nil and meta.__index) then
		objtype = object.__type
	end
	if objtype == nil and meta ~= nil then
		 objtype = meta.__type
	end
	return self.types:resolve(objtype)
end

function resolvekey(self, object, objtype)
	local key = nil
	local meta = getmetatable(object)
	if type(object) == "table" or (meta ~= nil and meta.__index) then
		key = object.__objkey
	end
	if key == nil and meta ~= nil then
		 key = meta.__objkey
	end
	if key == nil and objtype ~= nil then
		key = self.prefix..self:hashof(object)..self:hashof(objtype)
	end
	return key
end

function register(self, object, objkey, objtype)
	local except
	if objtype == nil then
		objtype, except = self:resolvetype(object)
	else
		objtype, except = self.types:resolve(objtype)
	end
	if not objtype then
		return nil, except
	end
	if objkey == nil then
		objkey = self:resolvekey(object, objtype)
	end
	return Servants.register(self, object, objkey, objtype)
end

function remove(self, objkey, objtype)
	local keytype = type(objkey)
	if keytype ~= "string" then
		local object = objkey
		if keytype == "table" then
			objkey = rawget(object, "__key")
			keytype = type(objkey)
		end
		if keytype ~= "string" then
			objkey = self:resolvekey(object)
			if objkey == nil then
				local except
				if objtype == nil then
					objtype, except = self:resolvetype(object)
				end
				if not objtype then                                                     --[[VERBOSE]] verbose:servants("unable to identify type of object ",object)
					return nil, except
				end
				objkey = self.prefix..self:hashof(object)..self:hashof(objtype)
			end
		end
	end
	return self:removeentry(objkey)
end

function retrieve(self, key)
	local result, except = Servants.retrieve(self, key)
	if result then result, except = result.object, result.type end
	return result, except
end
