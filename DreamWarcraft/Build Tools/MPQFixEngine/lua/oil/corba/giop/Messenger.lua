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
-- Title  : Client-side CORBA GIOP Protocol                                   --
-- Authors: Renato Maia <maia@inf.puc-rio.br>                                 --
--------------------------------------------------------------------------------
-- Notes:                                                                     --
--   See section 15.4.1 of CORBA 3.0 specification.                           --
--------------------------------------------------------------------------------
-- messenger:Facet
-- 	success:booelan, [except:table] = sendmsg(channel:object, type:number, header:table, types:table, values)
-- 	type:number, header:table, decoder:object = receivemsg(channel:object , [wait:boolean])
-- 
-- codec:Receptacle
-- 	encoder:object encoder()
-- 	decoder:object decoder(stream:string)
--------------------------------------------------------------------------------

local assert   = assert
local ipairs   = ipairs
local luapcall = pcall
local select   = select
local type     = type

local oo        = require "oil.oo"
local bit       = require "oil.bit"
local giop      = require "oil.corba.giop"
local Exception = require "oil.corba.giop.Exception"                            --[[VERBOSE]] local verbose = require "oil.verbose"

module("oil.corba.giop.Messenger", oo.class)

pcall = luapcall

--------------------------------------------------------------------------------

magictag    = giop.MagicTag
headersize  = giop.HeaderSize
headertype  = giop.Header_v1_[0]
messagetype = giop.MessageHeader_v1_[0]

header = {
	magic        = magictag,
	GIOP_version = {major=1, minor=0},
	byte_order   = (bit.endianess() == "little"),
	message_type = nil, -- defined later
	message_size = nil, -- defined later
}

--------------------------------------------------------------------------------

function sendmsg(self, channel, msgtype, message, types, values)                --[[VERBOSE]] verbose:message(true, "send message ",msgtype," ",message)
	--
	-- Create GIOP message body
	--
	local encoder = self.codec:encoder()
	encoder:shift(self.headersize) -- alignment accordingly to GIOP header size
	if message then
		encoder:put(message, self.messagetype[msgtype])
	end
	if types then
		local count = values.n or #values
		for index, idltype in ipairs(types) do
			local value
			if index <= count then
				value = values[index]
			end
			local ok, errmsg = self.pcall(encoder.put, encoder, value, idltype)
			if not ok then
				assert(type(errmsg) == "table", errmsg)
				return nil, errmsg
			end
		end
	end
	local stream = encoder:getdata()
	
	--
	-- Create GIOP message header
	--
	local header = self.header
	header.message_size = #stream
	header.message_type = msgtype
	encoder = self.codec:encoder()
	encoder:struct(header, self.headertype)
	stream = encoder:getdata()..stream
	
	--
	-- Send stream over the channel
	--
	local success, except, reset
	repeat
		channel:trylock("write", true)
		success, except = channel:send(stream)
		if not success then
			if except == "closed" then
				-- only clients have 'reset' op.
				if reset == nil and channel.reset then
					success, except = channel:reset()
					if success then
						reset, success, except = true, nil, nil 
					end
				else
					channel:close()
				end
			end
		-- else
			--TODO:[maia] How can I assure that someone is actually listening
			--            to this channel? Because if the server has closed
			--            the connection, we have received a FIN, but the RST
			--            may not have been received yet, so we might be sending
			--            data to a socket no one is listening to. (see page 132
			--            of R. Stevens, UNIX network programming, 2nd ed, 1997)
		end
		channel:freelock("write")
	until success or except
	if except then
		except = Exception{ "COMM_FAILURE", minor_code_value = 0,
			message = "unable to write into connection ("..except..")",
			reason = "closed",
			connection = channel,
		}
	end                                                                           --[[VERBOSE]] verbose:message(false)
	
	return success, except
end

--------------------------------------------------------------------------------

function receivemsg(self, channel)                                              --[[VERBOSE]] verbose:message(true, "receive message from channel")
	local success, except = channel:receive(self.headersize)
	if success then
		local decoder = self.codec:decoder(success)
		--
		-- Read GIOP message header
		--
		local header = self.headertype
		local magic = decoder:array(header[1].type)
		if magic == self.magictag then
			local version = decoder:struct(header[2].type)
			if version.major == 1 and version.minor == 0 then
				decoder:order(decoder:boolean())
				local type = decoder:octet()
				local size = decoder:ulong()
				--
				-- Read GIOP message body
				--
				if size > 0 then
					success, except = channel:receive(size)
				else
					success, except = "", nil
				end
				if success then
					decoder:append(success)
					success = type
					header = self.messagetype[type]
					if header then
						except = decoder:struct(header)
						channel = decoder
					elseif header == nil then
						success = nil
						except = Exception{ "INTERNAL", minor_code_value = 0,
							message = "GIOP 1.0 message type not supported",
							reason = "messageid",
							major = version.major,
							minor = version.minor,
							type = type,
						}
					end
				else
					if except == "closed" then channel:close() end
					except = Exception{ "COMM_FAILURE", minor_code_value = 0,
						message = "unable to read from connection ("..except..")",
						reason = "closed",
						connection = channel,
					}
				end
			else
				success = nil
				except = Exception{ "INTERNAL", minor_code_value = 0,
					message = "GIOP version not supported",
					reason = "version",
					procotol = "GIOP",
					version = version,
				}
			end
		else
			success = nil
			except = Exception{ "MARSHAL", minor_code_value = 8,
				message = "illegal GIOP message magic tag",
				reason = "magictag",
				tag = magic,
			}
		end
	else
		if except == "closed" then channel:close() end
		except = Exception{ "COMM_FAILURE", minor_code_value = 0,
			message = "unable to read from connection",
			reason = except,
			connection = channel,
		}
	end                                                                           --[[VERBOSE]] verbose:message(false, "got message ",success, except)
	return success, except, channel
end

--------------------------------------------------------------------------------
--------------------------------------------------------------------------------

--[[VERBOSE]] function verbose.custom:message(...)
--[[VERBOSE]] 	local viewer = self.viewer
--[[VERBOSE]] 	local output = viewer.output
--[[VERBOSE]] 	for i = 1, select("#", ...) do
--[[VERBOSE]] 		local value = select(i, ...)
--[[VERBOSE]] 		if giop.MessageType[value] then
--[[VERBOSE]] 			output:write(giop.MessageType[value])
--[[VERBOSE]] 		elseif type(value) == "string" then
--[[VERBOSE]] 			output:write(value)
--[[VERBOSE]] 		else
--[[VERBOSE]] 			viewer:write(value)
--[[VERBOSE]] 		end
--[[VERBOSE]] 	end
--[[VERBOSE]] end
