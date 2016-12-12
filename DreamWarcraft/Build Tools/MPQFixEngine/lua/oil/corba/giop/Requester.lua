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
--   See chapter 15 of CORBA 3.0 specification.                               --
--------------------------------------------------------------------------------
-- requests:Facet
-- 	channel:object getchannel(reference:table)
-- 	reply:object, [except:table], [requests:table] newrequest(channel:object, reference:table, operation:table, args...)
-- 	reply:object, [except:table], [requests:table] getreply(channel:object, [probe:boolean])
-- 
-- channels:HashReceptacle
-- 	channel:object retieve(configs:table)
-- 
-- profiler:HashReceptacle
-- 	info:table decode(stream:string)
-- 
-- mutex:Receptacle
-- 	locksend(channel:object)
-- 	freesend(channel:object)
--------------------------------------------------------------------------------

local assert   = assert
local ipairs   = ipairs
local newproxy = newproxy
local pairs    = pairs
local select   = select
local type     = type
local unpack   = unpack

local oo        = require "oil.oo"
local bit       = require "oil.bit"
local giop      = require "oil.corba.giop"
local Exception = require "oil.corba.giop.Exception"
local Messenger = require "oil.corba.giop.Messenger"                            --[[VERBOSE]] local verbose = require "oil.verbose"

module "oil.corba.giop.Requester"

oo.class(_M, Messenger)

--------------------------------------------------------------------------------

local IOR                = giop.IOR
local RequestID          = giop.RequestID
local ReplyID            = giop.ReplyID
local LocateRequestID    = giop.LocateRequestID
local LocateReplyID      = giop.LocateReplyID
local CloseConnectionID  = giop.CloseConnectionID
local MessageErrorID     = giop.MessageErrorID
local MessageType        = giop.MessageType
local SystemExceptionIDL = giop.SystemExceptionIDL

local Empty = {}

local COMPLETED_YES   = 0
local COMPLETED_NO    = 1
local COMPLETED_MAYBE = 2

--------------------------------------------------------------------------------
-- request id management for channels

function register(channel, request)
	local id = #channel + 1
	request.request_id = id
	request.channel = channel
	channel[id] = request                                                         --[[VERBOSE]] verbose:invoke("registering request with id ",id)
	return id
end

function unregister(channel, id)                                                --[[VERBOSE]] verbose:invoke("unregistering request with id ",id)
	local request = channel[id]
	if request then
		request.request_id = nil
		request.channel = nil
		channel[id] = nil
		return request
	end
end

--------------------------------------------------------------------------------

function getchannel(self, reference)                                            --[[VERBOSE]] verbose:invoke(true, "get communication channel")
	local result, except = reference._channel
	if result then                                                                --[[VERBOSE]] verbose:invoke(false, "reusing channel from preivous calls")
		return reference._channel, reference._objectkey, reference._profile
	end
	for _, profile in ipairs(reference.profiles) do                               --[[VERBOSE]] verbose:invoke("[IOR profile with tag ",profile.tag,"]")
		local tag = profile.tag
		local channels = self.channels[tag]
		local profiler = self.profiler[tag]
		if channels and profiler then
			profiler, except = profiler:decode(profile.profile_data)
			if profiler then
				reference._profiletag = tag
				reference._profiledata = profiler
				reference._objectkey = except
				result, except = channels:retrieve(profiler)
				if result then
					reference._channel = result                                           --[[VERBOSE]] verbose:invoke(false, "got channel from profile with tag ",profile.tag,"]")
					return result, reference._objectkey, reference._profile
				elseif except == "connection refused" then
					except = Exception{ "COMM_FAILURE",
						minor_code_value = 1,
						completion_status = COMPLETED_NO,
						reason = "closed",
						message = "connection to profile refused",
						profile = profiler,
					}
				elseif except == "too many open connections" then
					except = Exception{ "NO_RESOURCES",
						minor_code_value = 0,
						completion_status = COMPLETED_NO,
						reason = "resources",
						message = "too many open connections by protocol",
						protocol = tag,
					}
				end
			end
			break
 		end
	end
	if not except then                                                            --[[VERBOSE]] verbose:invoke("[no supported profile found]")
	 	except = Exception{ "IMP_LIMIT",
			minor_code_value = 1,
			completion_status = COMPLETED_NO,
			message = "no supported GIOP profile found",
			reason = "profiles",
		}
	end                                                                           --[[VERBOSE]] verbose:invoke(false)
	return nil, except
end

--------------------------------------------------------------------------------

function makerequest(self, channel, objectkey, operation, ...)
	local request = {
		request_id           = 0,
		response_expected    = not operation.oneway,
		service_context      = Empty,
		requesting_principal = Empty,
		object_key           = objectkey,
		operation            = operation.name,
		inputs               = operation.inputs,
		outputs              = operation.outputs,
		exceptions           = operation.exceptions,
		n                    = select("#", ...),
		...,
	}
	if channel and request.response_expected then
		register(channel, request)
	end
	return request
end

function sendrequest(self, reference, operation, ...)
	local channel, objectkey = self:getchannel(reference)
	if channel then
		local request = self:makerequest(channel, objectkey, operation, ...)        --[[VERBOSE]] verbose:invoke(true, "request ",request.request_id," for operation '",operation.name,"'")
		local result, except = self:sendmsg(channel, RequestID, request,
		                                    request.inputs, request)
		if result then
			if not request.response_expected then
				request.success = true
				request.n = 0
			end
			result, except = request, nil
		else
			unregister(channel, request.request_id)
		end                                                                         --[[VERBOSE]] verbose:invoke(false)
		return result, except
	end
	return nil, objectkey
end

function newrequest(self, reference, operation, ...)
	local requester = self.OperationRequester[operation.name] or self.sendrequest
	return requester(self, reference, operation, ...)
end

--------------------------------------------------------------------------------

function reissue(self, channel, request)                                        --[[VERBOSE]] verbose:invoke(true, "reissue request for operation '",request.operation,"'")
	register(channel, request)
	local success, except = self:sendmsg(channel, RequestID, request,
	                                     request.inputs, request)
	if not success then
		unregister(channel, request.request_id)
	end                                                                           --[[VERBOSE]] verbose:invoke(false, "reissue",success and "d successfully" or " failed")
	return success, except
end

local SystemExceptionReason = {
	["IDL:omg.org/CORBA/COMM_FAILURE:1.0"    ] = "closed",
	["IDL:omg.org/CORBA/MARSHAL:1.0"         ] = "marshal",
	["IDL:omg.org/CORBA/NO_IMPLEMENT:1.0"    ] = "noimplement",
	["IDL:omg.org/CORBA/BAD_OPERATION:1.0"   ] = "badoperation",
	["IDL:omg.org/CORBA/OBJECT_NOT_EXIST:1.0"] = "badkey",
}

function doreply(self, replied, header, decoder)
	local status = header.reply_status
	if status == "NO_EXCEPTION" then                                              --[[VERBOSE]] verbose:invoke("got successful reply for request ",header.request_id)
		local outputs = replied.outputs
		replied.success = true
		replied.n = #outputs
		for index, output in ipairs(outputs) do
			local ok, result = self.pcall(decoder.get, decoder, output)
			if not ok then
				assert(type(result) == "table", result)
				return nil, result
			end
			replied[index] = result
		end
	else -- status ~= "NO_EXCEPTION"
		local except
		if status == "LOCATION_FORWARD" then                                        --[[VERBOSE]] verbose:invoke("forwarding request ",header.request_id," through other channel")
			local success
			success, except = self:getchannel(decoder:struct(IOR))
			if success then
				success, except = self:reissue(success, replied)
				if success then
					return true -- do not do anything else and notify that reply
					            -- was handled successfully
				end
			end
		else -- status ~= ["LOCATION_FORWARD"|"NO_EXCEPTION"]
			if status == "USER_EXCEPTION" then                                        --[[VERBOSE]] verbose:invoke("got reply with exception for ",header.request_id)
				local repId = decoder:string()
				except = replied.exceptions[repId]
				if except then
					except = decoder:except(except)
					except[1] = repId
					except = Exception(except)
				else
					except = Exception{ "UNKNOWN",
						minor_code_value = 0,
						completion_status = COMPLETED_MAYBE,
						message = "unexpected user-defined exception",
						reason = "badexception",
						exception = repId,
					}
				end
			elseif status == "SYSTEM_EXCEPTION" then                                  --[[VERBOSE]] verbose:invoke("got reply with system exception for ",header.request_id)
				-- TODO:[maia] set its type to the proper SystemExcep.
				except = decoder:struct(SystemExceptionIDL)
				except[1] = except.exception_id
				except.reason = SystemExceptionReason[ except[1] ]
				except = Exception(except)
			else -- status == ???
				except = Exception{ "INTERNAL",
					minor_code_value = 0,
					completion_status = COMPLETED_MAYBE,
					message = "unsupported reply status",
					reason = "badreply",
					status = status,
				}
			end -- of if status == "USER_EXCEPTION"
		end -- of if status == "LOCATION_FORWARD"
		replied.success = false
		replied.n = 1
		replied[1] = except
	end -- of if status == "NO_EXCEPTION"
	local replier = self.OperationReplier[replied.operation]
	if replier then
		local success, except = replier(self, replied)
		if not success then
			return nil, except
		end
	end
	return true
end

function resetchannel(self, channel)
	local success, except = channel:reset()
	if success then                                                               --[[VERBOSE]] verbose:invoke(true, "reissue all pending requests")
		local requests = {}
		for id, pending in pairs(channel) do
			if type(id) == "number" then
				unregister(channel, id)
				requests[#requests+1] = pending
			end
		end
		local index = 0
		repeat
			index = index + 1
			local pending = requests[index]
			if pending == nil then break end
			success, except = self:reissue(channel, pending)
		until not success
		if not success then
			-- set error for all requests that are still pending in this channel
			for i = index, #requests do
				local pending = requests[i]
				pending.success = false
				pending.n = 1
				pending[1] = except
				channel:signal(pending)
			end
		end                                                                         --[[VERBOSE]] verbose:invoke(false, "reissue",success and "d successfully" or " failed")
	else
		if except == "connection refused" then
			except = Exception{ "COMM_FAILURE",
				minor_code_value = 1,
				completion_status = COMPLETED_MAYBE,
				reason = "closed",
				message = "unable to restablish channel",
				channel = channel,
			}
		elseif except == "too many open connections" then
			except = Exception{ "NO_RESOURCES",
				minor_code_value = 0,
				completion_status = COMPLETED_MAYBE,
				reason = "resources",
				message = "unbale to restablish channel, too many open connections",
				channel = channel,
			}
		else -- unknown error
			return success, except
		end
		for id, pending in pairs(channel) do
			if type(id) == "number" then
				unregister(channel, id)
				pending.success = false
				pending.n = 1
				pending[1] = except
				channel:signal(pending)
			end
		end
	end
	return true
end

function getreply(self, request, probe)
	local success, except = true, nil
	local continue = true
	while continue and (request.success == nil) do
		local channel = request.channel
		if channel:trylock("read", not probe, request) then
			while request.channel == channel do
				if probe and not channel:probe() then continue = false break end
				local msgid, header, decoder = self:receivemsg(channel)
				if msgid == ReplyID then
					local replied = unregister(channel, header.request_id)
					if replied then
						success, except = self:doreply(replied, header, decoder)
						channel:signal(replied)
					else -- replied == nil
						success, except = nil, Exception{ "INTERNAL",
							minor_code_value = 0,
							completion_status = COMPLETED_MAYBE,
							message = "unexpected request id",
							reason = "requestid",
							id = header.request_id,
						}
					end
				elseif (msgid == CloseConnectionID) or
				       (msgid == nil and header.reason == "closed") then                --[[VERBOSE]] verbose:invoke("got remote request to close channel or channel is broken")
					success, except = self:resetchannel(channel)
				elseif msgid == MessageErrorID then
					success, except = nil, Exception{ "COMM_FAILURE",
						minor_code_value = 0,
						completion_status = COMPLETED_MAYBE,
						reason = "server",
						message = "error in server message processing",
					}
				elseif MessageType[msgid] then
					success, except = nil, Exception{ "INTERNAL",
						minor_code_value = 0,
						completion_status = COMPLETED_MAYBE,
						reason = "unexpected",
						message = "unexpected GIOP message",
						message = MessageType[msgid],
						id = msgid,
					}
				elseif header.reason == "version" then                                  --[[VERBOSE]] verbose:invoke("got message with wrong version, send message error notification")
					success, except = self:sendmsg(channel, MessageErrorID)
				else -- not msgid and header.reason ~= ["version"|"closed"]
					success, except = nil, header
				end
				if not success then continue = false break end
			end -- of while current channel is from the reply should be read
			channel:freelock("read")
		elseif probe then
			continue = false
		end
	end
	return success, except
end
--------------------------------------------------------------------------------

OperationRequester = {}
OperationReplier = {}

local ReplyTrue  = {
	success = true,
	n = 1,
	true,
}
local ReplyFalse = {
	success = true,
	n = 1,
	false,
}

function OperationRequester:_is_equivalent(reference, _, otherref)
	otherref = otherref.__reference
	if otherref then
		local tags = {}
		for _, profile in ipairs(otherref.profiles) do
			tags[profile.tag] = profile
		end
		for _, profile in ipairs(reference.profiles) do
			local tag = profile.tag
			local other = tags[tag]
			if other then
				local profiler = self.profiler[tag]
				if
					profiler and
					profiler:equivalent(profile.profile_data, other.profile_data)
				then
					return ReplyTrue
				end
			end
		end
	end
	return ReplyFalse
end

local _non_existent = giop.ObjectOperations._non_existent
function OperationRequester:_non_existent(reference)
	local result, except = self:sendrequest(reference, _non_existent)
	if result and result.success == false then
		result, except = nil, result[1]
	end
	if not result and except.reason=="closed" then
		result, except = ReplyTrue, nil
	end
	return result, except
end
function OperationReplier:_non_existent(request)
	local except = request[1]
	if not request.success
	and ( except.exception_id == "IDL:omg.org/CORBA/OBJECT_NOT_EXIST:1.0" or
		    except.reason == "closed" )
	then
		request.success = true
		request.n = 1
		request[1] = true
	end
	return true
end
