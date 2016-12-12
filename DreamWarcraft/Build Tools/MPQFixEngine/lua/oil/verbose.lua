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
-- Release: 0.5                                                              --
-- Title  : Verbose Support                                                   --
-- Authors: Renato Maia <maia@inf.puc-rio.br>                                 --
--------------------------------------------------------------------------------

local rawget = rawget
local type   = type
local unpack = unpack

local math   = require "math"
local string = require "string"
local table  = require "table"

local ObjectCache = require "loop.collection.ObjectCache"
local Viewer      = require "loop.debug.Viewer"
local Verbose     = require "loop.debug.Verbose"
local Inspector   = require "loop.debug.Inspector"

module("oil.verbose", Verbose)

viewer = Viewer{
	maxdepth = 1,
	labels = ObjectCache(),
}
function viewer.labels:retrieve(value)
  local type = type(value)
  local id = rawget(self, type) or 0
  self[type] = id + 1
  local label = {}
  repeat
    label[#label + 1] = string.byte("A") + (id % 26)
    id = math.floor(id / 26)
  until id <= 0
  return string.format("%s:%s", type, string.char(unpack(label)))
end

function output(self, output)
	self.viewer.output = output
end

groups.broker = { "acceptor", "dispatcher", "servants", "proxies" }
groups.communication = { "mutex", "invoke", "listen", "message", "channels" }
groups.transport = { "marshal", "unmarshal" }
groups.idltypes = { "idl", "repository" }

_M:newlevel{ "broker" }
_M:newlevel{ "invoke", "listen" }
_M:newlevel{ "mutex" }
_M:newlevel{ "message" }
_M:newlevel{ "channels" }
_M:newlevel{ "transport" }
_M:newlevel{ "hexastream" }
_M:newlevel{ "idltypes" }

function _M:hexastream(codec, cursor, prefix)
	if self.flags.hexastream then
		local stream = codec:getdata()
		if prefix then stream = string.rep("\0", prefix)..stream end
		local last = #stream
		for count = 1, last do
			if cursor[count] then
				for count = last, count, -1 do
					if cursor[count] == false then
						last = math.min(last, 16*math.ceil(count/16))
						break
					end
				end
				local base = codec.previousend
				local output = self.viewer.output
				local lines = string.format("%%0%dx:", math.ceil(math.log10((base+last)/16))+1)
				local text = {}
				for count = count-(count-1)%16, last do
					column = math.mod(count-1, 16)
					-- write line start if necessary
					if column == 0 then
						output:write(lines:format(base+count-1))
					end
					-- write hexadecimal code
					local hexa
					if cursor[count]
						then hexa = "[%02x]"
						else hexa = " %02x "
					end
					local code = stream:byte(count, count)
					output:write(hexa:format(code))
					if code == 0 then
						text[#text+1] = "."
					elseif code == 255 then
						text[#text+1] = "#"
					elseif stream:match("^[%w%p ]", count) then
						text[#text+1] = stream:sub(count, count)
					else
						text[#text+1] = "?"
					end
					-- write blank if reached the end of the stream
					if count == last or cursor[count+1] == "end" then
						output:write(string.rep("    ", 15-column))
						text[#text+1] = string.rep(" ", 15-column)
						if column < 8 then output:write("  ") end
						column = 15
					end
					-- write ASCII text if last column, or a blank space if middle column
					if column == 15 then
						output:write("  |"..table.concat(text).."|\n")
						text = {}
					elseif column == 7 then
						output:write("  ")
					end
					if cursor[count+1] == "end" then break end
				end
				break
			end
		end
	end
end

--------------------------------------------------------------------------------

_M:flag("debug", true)
_M:flag("print", true)

I = Inspector{ viewer = viewer }
function inspect:debug() self.I:stop(4) end
