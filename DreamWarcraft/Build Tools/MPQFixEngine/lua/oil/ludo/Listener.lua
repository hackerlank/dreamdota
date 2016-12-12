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
-- Title  : Server-side LuDO Protocol                                         --
-- Authors: Renato Maia <maia@inf.puc-rio.br>                                 --
--------------------------------------------------------------------------------
-- listener:Facet
-- 	configs:table default([configs:table])
-- 	channel:object, [except:table] getchannel(configs:table)
-- 	request:object, [except:table], [requests:table] = getrequest(channel:object, [probe:boolean])
-- 
-- channels:Receptacle
-- 	channel:object retieve(configs:table)
-- 	configs:table default([configs:table])
-- 
-- codec:Receptacle
-- 	encoder:object encoder()
-- 	decoder:object decoder(stream:string)
--------------------------------------------------------------------------------

local select = select
local tonumber = tonumber
local unpack = unpack

local oo        = require "oil.oo"
local Exception = require "oil.Exception"                                       --[[VERBOSE]] local verbose = require "oil.verbose"

module("oil.ludo.Listener", oo.class)

oo.class(_M, Messenger)

--------------------------------------------------------------------------------

function setupaccess(self, configs)
	return self.channels:default(configs)
end

function freeaccess(self, accesspoint)                                          --[[VERBOSE]] verbose:listen("closing all channels with configs ",accesspoint)
	return self.channels:dispose(accesspoint)
end

--------------------------------------------------------------------------------

function getchannel(self, accesspoint, probe)
	return self.channels:retrieve(accesspoint, probe)
end

function putchannel(self, channel)                                              --[[VERBOSE]] verbose:listen "put channel back"
	return channel:release()
end

function freechannel(self, channel)                                             --[[VERBOSE]] verbose:listen "close channel"
	return channel:close()
end

--------------------------------------------------------------------------------

Request = oo.class{ n = 0 }

function Request:preinvoke()
	return self.objectkey, self.operation
end

function Request:params()
	return unpack(self, 1, self.n)
end

function Request:results(success, ...)
	local count = select("#", ...)
	self.success = success
	self.n = count
	for i = 1, count do
		self[i] = select(i, ...)
	end
end

--------------------------------------------------------------------------------

function newrequest(self, requestid, objectkey, operation, ...)                 --[[VERBOSE]] verbose:listen("got request for request ",requestid," to object ",objectkey,":",operation)
	return Request{
		requestid = requestid,
		objectkey = objectkey,
		operation = operation,
		n = select("#", ...),
		...,
	}
end

function getrequest(self, channel, probe)
	local result, except = true
	if channel:trylock("read", not probe) then
		if not probe or channel:probe() then
			result, except = channel:receive()
			if result then
				result = tonumber(result)
				if result then
					result, except = channel:receive(result)
					if result then
						local decoder = self.codec:decoder(result)
						result = self:newrequest(decoder:get())
						result.channel = channel
						channel[result.requestid] = result
					end
				else
					except = "LuDO protocol: invalid message size"
				end
			else
				if except == "closed" then                                              --[[VERBOSE]] verbose:listen("client closed the connection")
					channel:close()
					result, except = true, nil
				else
					except = "LuDO protocol: socket error "..except
				end
			end
		end
		channel:freelock("read")
	end
	return result, except
end

--------------------------------------------------------------------------------

local MessageFmt = "%d\n%s"

function sendreply(self, request)                                               --[[VERBOSE]] verbose:listen("got reply for request ",request.requestid," to object ",request.objectkey,":",request.operation)
	local channel = request.channel
	local encoder = self.codec:encoder()
	encoder:put(request.requestid, request.success, unpack(request, 1, request.n))
	channel[request.requestid] = nil
	local data = encoder:__tostring()
	channel:trylock("write", true)
	local result, except = channel:send(MessageFmt:format(#data, data))
	channel:freelock("write")
	if not result then
		if except == "closed" then                                                  --[[VERBOSE]] verbose:listen("client closed the connection")
			channel:close()
			result, except = true, nil
		else
			except = "LuDO protocol: socket error "..except
		end
	end
	return result, except
end
