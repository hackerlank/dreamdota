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
-- Title  : Client-side LuDO Protocol                                         --
-- Authors: Renato Maia <maia@inf.puc-rio.br>                                 --
--------------------------------------------------------------------------------
-- requests:Facet
-- 	reply:object, [except:table], [requests:table] newrequest(reference:table, operation, args...)
-- 	reply:object, [except:table], [requests:table] getreply(request:object, [probe:boolean])
-- 
-- codec:Receptacle
-- 	encoder:object encoder()
-- 	decoder:object decoder(stream:string)
-- 
-- channels:Receptacle
-- 	channel:object retieve(configs:table)
--------------------------------------------------------------------------------

local select  = select
local tonumber = tonumber
local unpack = unpack

local oo = require "oil.oo"                                                     --[[VERBOSE]] local verbose = require "oil.verbose"

module "oil.ludo.Requester"

oo.class(_M, Messenger)

--------------------------------------------------------------------------------

local MessageFmt = "%d\n%s"

function newrequest(self, reference, operation, ...)
	local result, except = self.channels:retrieve(reference)
	if result then
		local channel = result
		local encoder = self.codec:encoder()
		local requestid = #channel+1
		encoder:put(requestid, reference.object, operation, ...)
		local data = encoder:__tostring()
		channel:trylock("write", true)
		result, except = channel:send(MessageFmt:format(#data, data))
		channel:freelock("write")
		if result then
			result = { channel = channel }
			channel[requestid] = result
		else
			if except == "closed" then channel:close() end
		end
	end
	return result, except
end

--------------------------------------------------------------------------------

local function update(channel, requestid, success, ...)
	local request, except = channel[requestid]
	if request then
		channel[requestid] = nil
		request.channel = nil
		request.success = success
		request.n = select("#", ...)
		for i = 1, request.n do
			request[i] = select(i, ...)
		end
	else
		except = "LuDO protocol: unexpected reply"
	end
	return request, except
end

function getreply(self, request, probe)
	local result, except = true, nil
	if request.success == nil then
		local channel = request.channel
		if channel:trylock("read", not probe, request) then
			local codec = self.codec
			while result and (result ~= request) and (not probe or channel:probe()) do
				result, except = channel:receive()
				if result then
					result = tonumber(result)
					if result then
						result, except = channel:receive(result)
						if result then
							result, except = update(channel, codec:decoder(result):get())
							if result then
								channel:signal(result)
							end
						end
					else
						except = "LuDO protocol: invalid message size"
					end
				end
			end
			channel:freelock("read")
		end
	end
	return result, except
end
