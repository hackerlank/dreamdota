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
--------------------------------------------------------------------------------

local getmetatable = getmetatable
local rawget       = rawget
local rawset       = rawset
local setmetatable = setmetatable
local luatostring  = tostring
local type         = type

local table = require "loop.table"
local ObjectCache = require "loop.collection.ObjectCache"

local oo = require "oil.oo"
local Exception = require "oil.Exception"                                       --[[VERBOSE]] local verbose = require "oil.verbose"

module("oil.kernel.base.Servants", oo.class)

prefix = "_"

--------------------------------------------------------------------------------
-- Servant object proxy

local function deactivate(self)
	return self.__manager:removeentry(self.__key)
end

local function wrappertostring(self)
	return self.__manager.referrer:encode(self.__reference)
end

local function wrapperindexer(self, key)
	local value = self.__newindex[key]
	if type(value) == "function"
		then return self.__methods[value]
		else return value
	end
end

--------------------------------------------------------------------------------
--------------------------------------------------------------------------------

function __init(self, ...)
	self = oo.rawnew(self, ...)
	self.map = self.map or {}
	return self
end

function addentry(self, key, entry)
	local result, except = self.map[key]
	if result then
		if result == entry then
			result = true
		else
			result, except = nil, Exception{
				reason = "usedkey",
				message = "object key already in use",
				key = key,
			}
		end
	else                                                                          --[[VERBOSE]] verbose:servants("object ",entry," registered with key ",key)
		self.map[key] = entry
		result = true
	end
	return result, except
end

function removeentry(self, key)
	local map = self.map
	local entry = map[key]
	if entry ~= nil then                                                          --[[VERBOSE]] verbose:servants("object ",entry," with key ",key," removed")
		map[key] = nil
		return entry
	end
	return nil, Exception{
		reason = "usedkey",
		message = "unknown object key",
		key = key,
	}
end

function hashof(self, object)
	local meta = getmetatable(object)
	local backup
	if meta then
		backup = rawget(meta, "__tostring")
		if backup ~= nil then rawset(meta, "__tostring", nil) end
	end
	local hash = luatostring(object)
	if meta then
		if backup ~= nil then rawset(meta, "__tostring", backup) end
	end
	return hash:match("%l+: (%w+)") or hash
end
--------------------------------------------------------------------------------
--------------------------------------------------------------------------------

function setaccessinfo(self, ...)
	local result, except = true
	local accessinfo = self.accessinfo
	if not accessinfo then
		self.accessinfo = {...}
	else
		result, except = nil, Exception{
			reason = "configuration",
			message = "attempt to set access info twice",
			accessinfo = accessinfo,
		}
	end
	return result, except
end

--------------------------------------------------------------------------------
--------------------------------------------------------------------------------

function resolvekey(self, object)
	local key = nil
	local meta = getmetatable(object)
	if type(object) == "table" or (meta ~= nil and meta.__index) then
		key = object.__objkey
	end
	if key == nil and meta ~= nil then
		 key = meta.__objkey
	end
	if key == nil then
		key = self.prefix..self:hashof(object)
	end
	return key
end

function register(self, object, key, ...)
	if key == nil then
		key = self:resolvekey(object)
	end
	local result, except = self:addentry(key, object, ...)
	if result then
		result, except = self.referrer:newreference(self.accesspoint, key, ...)
		if result then
			result = {
				_deactivate = deactivate, -- TODO[maia]: DEPRECATED!
				__deactivate = deactivate,
				__manager = self,
				__key = key,
				__tostring = wrappertostring,
				__index = wrapperindexer,
				__newindex = object,
				__reference = result,
				__methods = ObjectCache{
					retrieve = function(_, method)
						return function(_, ...)
							return method(object, ...)
						end
					end
				}
			}
			setmetatable(result, result)
		else
			self:removeentry(key)
		end
	end
	return result, except
end

function remove(self, key)
	local keytype = type(key)
	if keytype ~= "string" then
		local object = key
		if keytype == "table" then
			key = rawget(object, "__key") -- is it a servant?
			keytype = type(key)
		end
		if keytype ~= "string" then
			local except
			key, except = self:resolvekey(object)
			if not key then                                                           --[[VERBOSE]] verbose:servants("unbale to identify key of object ",entry)
				return nil, except
			end
		end
	end
	return self:removeentry(key)
end

function retrieve(self, key)
	return self.map[key]
end
