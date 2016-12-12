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
-- 	channel:object dispose(configs:table)
-- 	configs:table default([configs:table])
-- 
-- sockets:Receptacle
-- 	socket:object tcp()
-- 	input:table, output:table select([input:table], [output:table], [timeout:number])
--------------------------------------------------------------------------------

local pairs = pairs
local type  = type

local tabop       = require "loop.table"
local ObjectCache = require "loop.collection.ObjectCache"
local OrderedSet  = require "loop.collection.OrderedSet"
local Wrapper     = require "loop.object.Wrapper"

local oo = require "oil.oo"                                                     --[[VERBOSE]] local verbose = require "oil.verbose"

module("oil.kernel.base.Channels", oo.class)

--------------------------------------------------------------------------------
--------------------------------------------------------------------------------

local function dummy() return true end

LuaSocketOps = {
	trylock  = dummy,
	freelock = dummy,
	signal   = dummy,
}

CoSocketOps = {}

function CoSocketOps:trylock(operation, wait, signal)
	local scheduler = self.cosocket.scheduler
	local thread = scheduler.current
	if not self[operation] then                                                   --[[VERBOSE]] verbose:mutex("channel free for ",operation)
		self[operation] = thread
	elseif wait and self[operation] ~= thread then                                --[[VERBOSE]] verbose:mutex("channel locked for ",operation,", waiting notification")
		local waiting = self.waiting[operation]
		waiting:enqueue(thread)
		if signal ~= nil then self[signal] = thread end
		scheduler:suspend()                                                         --[[VERBOSE]] verbose:mutex("notification received")
		if signal ~= nil then self[signal] = nil end
		waiting:remove(thread)
	end
	return self[operation] == thread
end

function CoSocketOps:signal(signal)
	local thread = self[signal]
	if thread then
		self.cosocket.scheduler:resume(thread)
		return true
	end
end

function CoSocketOps:freelock(operation)
	local scheduler = self.cosocket.scheduler
	if self[operation] == scheduler.current then
		local thread = self.waiting[operation]:first()
		if thread then                                                              --[[VERBOSE]] verbose:mutex("trasfering lock for ",operation," to other thread")
			self[operation] = thread
			scheduler:resume(thread)
		else                                                                        --[[VERBOSE]] verbose:mutex("releasing lock for ",operation)
			self[operation] = nil
			-- this would be a bad optimization: self.waiting[operation] = nil
		end
	end
end

--------------------------------------------------------------------------------
-- setup of TCP socket options

function setupsocket(self, socket, ...)
	if socket then
		local options = self.options
		if options then
			for name, value in pairs(options) do
				socket:setoption(name, value)
			end
		end
		
		-- additional socket operations
		if type(socket) ~= "table" then
			socket = Wrapper{ __object = socket }
			customops = self.LuaSocketOps
		else
			customops = self.CoSocketOps
			socket.waiting = ObjectCache{
				retrieve = function()
					return OrderedSet()
				end
			}
		end
		if customops then
			tabop.copy(customops, socket)
		end
	end
	return socket, ...
end
