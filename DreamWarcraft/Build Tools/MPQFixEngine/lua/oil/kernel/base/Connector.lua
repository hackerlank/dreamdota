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
-- Notes:                                                                     --
--   See section 15.7 of CORBA 3.0 specification.                             --
--   See section 13.6.10.3 of CORBA 3.0 specification for IIOP corbaloc.      --
--------------------------------------------------------------------------------
-- channels:Facet
-- 	channel:object retieve(configs:table, [probe:boolean])
-- 
-- sockets:Receptacle
-- 	socket:object tcp()
-- 	input:table, output:table select([input:table], [output:table], [timeout:number])
--------------------------------------------------------------------------------

local next         = next
local pairs        = pairs
local setmetatable = setmetatable
local type         = type

local tabop = require "loop.table"

local ObjectCache = require "loop.collection.ObjectCache"
local Wrapper     = require "loop.object.Wrapper"
local Channels    = require "oil.kernel.base.Channels"

local oo = require "oil.oo"                                                     --[[VERBOSE]] local verbose = require "oil.verbose"

module "oil.kernel.base.Connector"

oo.class(_M, Channels)

--------------------------------------------------------------------------------
-- connection management

LuaSocketOps = tabop.copy(Channels.LuaSocketOps)
CoSocketOps = tabop.copy(Channels.CoSocketOps)

function LuaSocketOps:close()
	local ports = self.factory.cache[self.host]
	ports[self.port] = nil
	if next(ports) == nil then
		self.factory.cache[self.host] = nil
	end
	return self.__object:close()
end

CoSocketOps.close = LuaSocketOps.close

function LuaSocketOps:reset()                                                   --[[VERBOSE]] verbose:channels("resetting channel (attempt to reconnect)")
	self.__object:close()
	local sockets = self.factory.sockets
	local result, errmsg = sockets:tcp()
	if result then
		local socket = result
		result, errmsg = socket:connect(self.host, self.port)
		if result then
			self.__object = socket
		end
	end
	return result, errmsg
end
function CoSocketOps:reset()                                                    --[[VERBOSE]] verbose:channels("resetting channel (attempt to reconnect)")
	self.__object:close()
	local sockets = self.factory.sockets
	local result, errmsg = sockets:tcp()
	if result then
		local socket = result
		result, errmsg = socket:connect(self.host, self.port)
		if result then
			self.__object = socket.__object
		end
	end
	return result, errmsg
end

local list = {}
function LuaSocketOps:probe()
	list[1] = self.__object
	return self.factory.sockets:select(list, nil, 0)[1] == list[1]
end
function CoSocketOps:probe()
	local list = { self }
	return self.factory.sockets:select(list, nil, 0)[1] == list[1]
end

--------------------------------------------------------------------------------
-- channel cache for reuse

SocketCache = oo.class{ __index = ObjectCache.__index, __mode = "v" }

function __init(self, object)
	self = oo.rawnew(self, object)
	--
	-- cache of active channels
	-- self.cache[host][port] == <channel to host:port>
	--
	self.cache = ObjectCache()
	function self.cache.retrieve(_, host)
		local cache = SocketCache()
		function cache.retrieve(_, port)
			local sockets = self.sockets
			local socket, errmsg = sockets:tcp()
			if socket then                                                            --[[VERBOSE]] verbose:channels("new socket to ",host,":",port)
				local success
				success, errmsg = socket:connect(host, port)
				if success then
					socket = self:setupsocket(socket)
					socket.factory = self
					socket.host = host
					socket.port = port
					return socket
				else
					self.except = "connection refused"
				end
			else
				self.except = "too many open connections"
			end
		end
		cache[cache.retrieve] = true -- avoid being collected as unused sockets
		return cache
	end
	return self
end

--------------------------------------------------------------------------------
-- channel factory

function retrieve(self, profile)                                                --[[VERBOSE]] verbose:channels("retrieve channel connected to ",profile.host,":",profile.port)
	local channel = self.cache[profile.host][profile.port]
	if channel then
		return channel
	else
		return nil, self.except
	end	
end
