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
-- references:Facet
-- 	reference:table newreference(objectkey:string, accesspointinfo:table...)
-- 	reference:string encode(reference:table)
-- 	reference:table decode(reference:string)
--------------------------------------------------------------------------------

local tonumber = tonumber

local socket = require "socket.core"

local oo = require "oil.oo"                                                     --[[VERBOSE]] local verbose = require "oil.verbose"

module("oil.ludo.Referrer", oo.class)

--------------------------------------------------------------------------------
--------------------------------------------------------------------------------

function newreference(self, access, key)
	local host = access.host
	if host == "*" then
		host = socket.dns.gethostname()
		host = socket.dns.toip(host) or host
	end
	return {
		host = host,
		port = access.port,
		object = key,
	}
end

function islocal(self, reference, access)
	if access.addresses[reference.host] and reference.port == access.port then
		return reference.object
	end
end

function encode(self, reference)
	local object, host, port = reference.object, reference.host, reference.port
	if object ~= nil and host ~= nil and port ~= nil then
		local encoder = self.codec:encoder()
		encoder:put(object, host, port)
		return encoder:__tostring()
	end
	return nil, "bad LuDO reference"
end

function decode(self, reference)
	local decoder = self.codec:decoder(reference)
	local object, host, port = decoder:get()
	if object ~= nil and host ~= nil and port ~= nil then
		return {
			host = host,
			port = port,
			object = object,
		}
	end
	return nil, "invalid LuDO reference"
end
