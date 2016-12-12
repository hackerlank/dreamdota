--------------------------------------------------------------------------------
---------------------- ##       #####    #####   ######  -----------------------
---------------------- ##      ##   ##  ##   ##  ##   ## -----------------------
---------------------- ##      ##   ##  ##   ##  ######  -----------------------
---------------------- ##      ##   ##  ##   ##  ##      -----------------------
---------------------- ######   #####    #####   ##      -----------------------
----------------------                                   -----------------------
----------------------- Lua Object-Oriented Programming ------------------------
--------------------------------------------------------------------------------
-- Project: LOOP Class Library                                                --
-- Release: 2.3 beta                                                          --
-- Title  : Cooperative Threads Scheduler with Integrated I/O                 --
-- Author : Renato Maia <maia@inf.puc-rio.br>                                 --
--------------------------------------------------------------------------------

--[[VERBOSE]] local rawget   = rawget
--[[VERBOSE]] local tostring = tostring

local ipairs            = ipairs
local getmetatable      = getmetatable
local math              = require "math"
local oo                = require "loop.simple"
local UnorderedArraySet = require "loop.collection.UnorderedArraySet"
local Scheduler         = require "loop.thread.Scheduler"

module "loop.thread.IOScheduler"

oo.class(_M, Scheduler)

--------------------------------------------------------------------------------
-- Initialization Code ---------------------------------------------------------
--------------------------------------------------------------------------------

local DoubleMap = oo.class()
function DoubleMap:__init(...)
	self = oo.rawnew(self, ...)
	self.socks = UnorderedArraySet()
	return self
end
function DoubleMap:add(key, value)
	self.socks:add(key)
	self[key] = value
	self[value] = key
end
function DoubleMap:remove(key)
	local value = self[key]
	if key ~= nil then
		self.socks:remove(key)
		self[key] = nil
		self[value] = nil
		return value, key
	end
end

function __init(class, self)
	self = Scheduler.__init(class, self)
	self.readlocks = {}
	self.writelocks = {}
	self.reading = DoubleMap()
	self.writing = DoubleMap()
	return self
end
__init(getmetatable(_M), _M)

--------------------------------------------------------------------------------
-- Internal Functions ----------------------------------------------------------
--------------------------------------------------------------------------------

function signalall(self, timeout)                                               --[[VERBOSE]] local verbose = self.verbose
	if timeout then timeout = math.max(timeout - self:time(), 0) end
	local reading, writing = self.reading, self.writing
	if #reading.socks > 0 or #writing.socks > 0 then                              --[[VERBOSE]] verbose:scheduler("signaling blocked threads for ",timeout," seconds")
		local running = self.running
		local readok, writeok = self.select(reading.socks, writing.socks, timeout)
		for _, channel in ipairs(readok) do
			running:enqueue(reading:remove(channel))
		end
		for _, channel in ipairs(writeok) do
			running:enqueue(writing:remove(channel))
		end
		return true
	elseif timeout and timeout > 0 then                                           --[[VERBOSE]] verbose:scheduler("no threads blocked, sleeping for ",timeout," seconds")
		self.sleep(timeout)
	end
	return false
end

--------------------------------------------------------------------------------
-- Customizable Behavior -------------------------------------------------------
--------------------------------------------------------------------------------

idle = signalall

--------------------------------------------------------------------------------
-- Exported API ----------------------------------------------------------------
--------------------------------------------------------------------------------

function register(self, routine, previous)
	local reading, writing = self.reading, self.writing
	for _, channel in ipairs(reading) do
		if reading[channel] == routine then return end
	end
	for _, channel in ipairs(writing) do
		if writing[channel] == routine then return end
	end
	return Scheduler.register(self, routine, previous)
end

local function handleremoved(self, routine, removed, ...)
	local reading, writing = self.reading, self.writing
	local channel = reading[routine]
	if channel then
		reading:remove(channel)
		self.readlocks[channel] = nil
		removed = routine
	end
	local channel = writing[routine]
	if channel then
		writing:remove(channel)
		self.writelocks[channel] = nil
		removed = routine
	end
	return removed, ...
end
function remove(self, routine)
	return handleremoved(self, routine, Scheduler.remove(self, routine))
end

--------------------------------------------------------------------------------
-- Control Functions -----------------------------------------------------------
--------------------------------------------------------------------------------

function step(self, ...)                                                        --[[VERBOSE]] local verbose = self.verbose; verbose:scheduler(true, "performing scheduling step")
	local signaled = self:signalall(0)
	local wokenup = self:wakeupall()
	local resumed = self:resumeall(nil, ...)                                      --[[VERBOSE]] verbose:scheduler(false, "scheduling step performed")
	return signaled or wokenup or resumed
end

--------------------------------------------------------------------------------
-- Verbose Support -------------------------------------------------------------
--------------------------------------------------------------------------------

--[[VERBOSE]] local oldfunc = verbose.custom.threads
--[[VERBOSE]] function verbose.custom:threads(...)
--[[VERBOSE]] 	local viewer  = self.viewer
--[[VERBOSE]] 	local output  = self.viewer.output
--[[VERBOSE]] 	
--[[VERBOSE]] 	oldfunc(self, ...)
--[[VERBOSE]] 	
--[[VERBOSE]] 	local scheduler = rawget(self, "schedulerdetails")
--[[VERBOSE]] 	if scheduler then
--[[VERBOSE]] 		local newline = "\n"..viewer.prefix..viewer.indentation
--[[VERBOSE]] 	
--[[VERBOSE]] 		output:write(newline)
--[[VERBOSE]] 		output:write("Reading:")
--[[VERBOSE]] 		for _, socket in ipairs(scheduler.reading.socks) do
--[[VERBOSE]]				local current = scheduler.reading[socket]
--[[VERBOSE]] 			output:write(" ")
--[[VERBOSE]] 			output:write(tostring(self.labels[current]))
--[[VERBOSE]] 			output:write(" (")
--[[VERBOSE]] 			output:write(tostring(self.labels[socket]))
--[[VERBOSE]] 			output:write(")")
--[[VERBOSE]] 		end
--[[VERBOSE]] 	
--[[VERBOSE]] 		output:write(newline)
--[[VERBOSE]] 		output:write("Writing:")
--[[VERBOSE]] 		for _, socket in ipairs(scheduler.writing.socks) do
--[[VERBOSE]]				local current = scheduler.writing[socket]
--[[VERBOSE]] 			output:write(" ")
--[[VERBOSE]] 			output:write(tostring(self.labels[current]))
--[[VERBOSE]] 			output:write(" (")
--[[VERBOSE]] 			output:write(tostring(self.labels[socket]))
--[[VERBOSE]] 			output:write(")")
--[[VERBOSE]] 		end
--[[VERBOSE]] 	end
--[[VERBOSE]] end
