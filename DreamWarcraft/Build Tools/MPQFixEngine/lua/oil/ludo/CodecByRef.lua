--------------------------------------------------------------------------------
------------------------------  #####      ##     ------------------------------
------------------------------ ##   ##  #  ##     ------------------------------
------------------------------ ##   ## ##  ##     ------------------------------
------------------------------ ##   ##  #  ##     ------------------------------
------------------------------  #####  ### ###### ------------------------------
--------------------------------                --------------------------------
----------------------- An Object Request Broker in Lua ------------------------
--------------------------------------------------------------------------------
-- Project: OiL - ORB in Lua                                                  --
-- Release: 0.5                                                               --
-- Title  : Client-side CORBA GIOP Protocol specific to IIOP                  --
-- Authors: Renato Maia <maia@inf.puc-rio.br>                                 --
--------------------------------------------------------------------------------
-- channels:Facet
-- 	channel:object retieve(configs:table)
-- 	channel:object select(channel|configs...)
-- 	configs:table default(configs:table)
-- 
-- sockets:Receptacle
-- 	socket:object tcp()
-- 	input:table, output:table select([input:table], [output:table], [timeout:number])
--------------------------------------------------------------------------------

local getmetatable = getmetatable
local pairs = pairs
local tonumber = tonumber
local tostring = tostring
local rawget = rawget
local rawset = rawset

local table        = require "loop.table"
local StringStream = require "loop.serial.StringStream"

local oo    = require "oil.oo"
local Codec = require "oil.ludo.Codec"                                             --[[VERBOSE]] local verbose = require "oil.verbose"

module "oil.ludo.CodecByRef"

oo.class(_M, Codec)

--------------------------------------------------------------------------------
--------------------------------------------------------------------------------

-- TODO:[maia] copied from loop.serial.Serializer. Make it a member function
local function getidfor(value)
	local meta = getmetatable(value)
	local backup
	if meta then
		backup = rawget(meta, "__tostring")
		if backup ~= nil then rawset(meta, "__tostring", nil) end
	end
	local id = tostring(value):match("%l+: (%w+)")
	if meta then
		if backup ~= nil then rawset(meta, "__tostring", backup) end
	end
	return tonumber(id, 16) or id
end

local function serialproxy(self, value, id)                                     --[[VERBOSE]] verbose:marshal("marshalling proxy for value ",value)
	self[value] = self.namespace..":value("..id..")"
	self:write(self.namespace,":value(",id,",'table',")
	self:write("proxies:resolve(")
	local reference = self.servants:register(value).__reference
	StringStream.table(self, reference, getidfor(reference))
	self:write("))")
end

local function serialtable(self, value, id)                                     --[[VERBOSE]] verbose:marshal(true, "marshalling of table ",value)
	local reference = rawget(value, "__reference")
	if reference then                                                             --[[VERBOSE]] verbose:marshal "table is a proxy"
		self[value] = self.namespace..":value("..id..")"
		self:write(self.namespace,":value(",id,",'table',")
		self:write("proxies:resolve(")
		StringStream.table(self, reference, getidfor(reference))
		self:write("))")
	else
		local meta = getmetatable(value)
		if meta and meta.__marshalcopy then                                         --[[VERBOSE]] verbose:marshal "table by copy"
			StringStream.table(self, value, id)
		else                                                                        --[[VERBOSE]] verbose:marshal "table by reference"
			serialproxy(self, value, id)
		end                                                                         --[[VERBOSE]] verbose:marshal(false)
	end
end

local LuDOStream = oo.class({
	table        = serialtable,
	thread       = serialproxy,
	userdata     = serialproxy,
	["function"] = serialproxy,
}, StringStream)

function encoder(self)
	return LuDOStream(table.copy(self.names, {servants = self.servants}))
end

function decoder(self, stream)
	return StringStream{
		environment = table.copy(self.values, {proxies = self.proxies}),
		data = stream,
	}
end
