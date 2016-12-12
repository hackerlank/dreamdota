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
-- Title  : Interface Definition Language (IDL) compiler                      --
-- Authors: Renato Maia   <maia@inf.puc-rio.br>                               --
--          Ricardo Cosme <rcosme@tecgraf.puc-rio.br>                         --
--------------------------------------------------------------------------------
-- compiler:Facet
-- 	success:boolean, [except:table] load(idl:string)
-- 	success:boolean, [except:table] loadfile(filepath:string)
-- 
-- registry:Receptacle
-- 	types:table register(definition:table)
--------------------------------------------------------------------------------

local pairs  = pairs
local select = select
local unpack = unpack

local table  = require "loop.table"
local luaidl = require "luaidl"

local oo  = require "oil.oo"
local idl = require "oil.corba.idl"                                             --[[VERBOSE]] local verbose = require "oil.verbose"

module("oil.corba.idl.Compiler", oo.class)

context = false

--------------------------------------------------------------------------------
DefaultOptions = {
	callbacks = {
		VOID      = idl.void,
		SHORT     = idl.short,
		LONG      = idl.long,
		LLONG     = idl.longlong,
		USHORT    = idl.ushort,
		ULONG     = idl.ulong,
		ULLONG    = idl.ulonglong,
		FLOAT     = idl.float,
		DOUBLE    = idl.double,
		LDOUBLE   = idl.longdouble,
		BOOLEAN   = idl.boolean,
		CHAR      = idl.char,
		OCTET     = idl.octet,
		ANY       = idl.any,
		TYPECODE  = idl.TypeCode,
		STRING    = idl.string,
		OBJECT    = idl.object,
		VALUEBASE = idl.ValueBase,
		operation = idl.operation,
		attribute = idl.attribute,
		except    = idl.except,
		union     = idl.union,
		struct    = idl.struct,
		enum      = idl.enum,
		array     = idl.array,
		sequence  = idl.sequence,
		valuetype = idl.valuetype,
		valuebox  = idl.valuebox,
		typedef   = idl.typedef,
	},
}

function DefaultOptions.callbacks.interface(def)
	if def.definitions then -- not forward declarations
		--<PROBLEM WITH LUAIDL>
		--if def.abstract then
		--	return idl.abstract_interface(def)
		--end
		--</PROBLEM WITH LUAIDL>
		return idl.interface(def)
	end
	return def
end

local Modules
function DefaultOptions.callbacks.module(def)
	Modules[def] = true
	return def
end

function DefaultOptions.callbacks.start()
	Modules = {}
end

function DefaultOptions.callbacks.finish()
	for module in pairs(Modules) do idl.module(module) end
end

--------------------------------------------------------------------------------

function __init(self, ...)
	self = oo.rawnew(self, ...)
	self.defaults = table.copy(DefaultOptions)
	return self
end

function doresults(self, ...)
	if ... then
		return self.context.__component:register(...)
	end
	return ...
end

function options(self, idlpaths)
	local options = self.defaults
	if idlpaths then
		options = table.copy(options)
		local incpath = table.copy(options.incpath)
		for index, incpath in ipairs(idlpaths) do
			incpath[#incpath+1] = incpath
		end
		options.incpath = incpath
	end
	return options
end

function loadfile(self, filepath, idlpaths)
	return self:doresults(luaidl.parsefile(filepath, self:options(idlpaths)))
end

function load(self, idlspec, idlpaths)
	return self:doresults(luaidl.parse(idlspec, self:options(idlpaths)))
end
