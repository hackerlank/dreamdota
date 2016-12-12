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
-- Release: 0.5                                                               --
-- Title  : Request Acceptor                                                  --
-- Authors: Renato Maia <maia@inf.puc-rio.br>                                 --
--------------------------------------------------------------------------------
-- acceptor:Facet
-- 	configs:table, [except:table] setupaccess([configs:table])
-- 	success:boolean, [except:table] hasrequest(configs:table)
-- 	success:boolean, [except:table] acceptone(configs:table)
-- 	success:boolean, [except:table] acceptall(configs:table)
-- 	success:boolean, [except:table] halt(configs:table)
-- 
-- listener:Receptacle
-- 	configs:table default([configs:table])
-- 	channel:object, [except:table] getchannel(configs:table)
-- 	success:boolean, [except:table] freeaccess(configs:table)
-- 	success:boolean, [except:table] freechannel(channel:object)
-- 	request:table, [except:table] = getrequest(channel:object, [probe:boolean])
-- 	success:booelan, [except:table] = sendreply(request:table, success:booelan, results...)
-- 
-- dispatcher:Receptacle
-- 	success:boolean, [except:table]|results... dispatch(objectkey:string, operation:string|function, params...)
--------------------------------------------------------------------------------


local oo        = require "oil.oo"
local Exception = require "oil.Exception"                                       --[[VERBOSE]] local verbose = require "oil.verbose"

module("oil.kernel.base.Receiver", oo.class)

function processrequest(self, request)
	self.dispatcher:dispatch(request)
	return self.listener:sendreply(request)
end

--------------------------------------------------------------------------------

function initialize(self, config)
	local result, except = self.listener:setupaccess(config)
	if result then
		self.accesspoint = result
	end
	return result, except
end

function hasrequest(self)
	return self.listener:getchannel(self.accesspoint, true)
end

function acceptone(self)                                                        --[[VERBOSE]] verbose:acceptor(true, "accept one request from channel ",self.accesspoint)
	local result, except
	local listener = self.listener
	result, except = listener:getchannel(self.accesspoint)
	if result then
		local channel = result
		result, except = listener:getrequest(channel)
		if (result and result ~= true)
		or (not result and except.reason ~= "closed") then
			listener:putchannel(channel)
		end
		if result and result ~= true then                                           --[[VERBOSE]] verbose:acceptor(true, "dispatching request from accepted channel")
			result, except = self:processrequest(result)                              --[[VERBOSE]] verbose:acceptor(false)
		end
	end                                                                           --[[VERBOSE]] verbose:acceptor(false)
	return result, except
end

function acceptall(self)
	local listener = self.listener
	local accesspoint = self.accesspoint                                          --[[VERBOSE]] verbose:acceptor(true, "accept all requests from channel ",accesspoint)
	local result, except
	self[accesspoint] = true
	repeat
		result, except = listener:getchannel(accesspoint)
		if result then
			local channel = result
			result, except = listener:getrequest(channel)
			if (result and result ~= true)
			or (not result and except.reason ~= "closed") then
				listener:putchannel(channel)
			end
			if result and result ~= true then                                         --[[VERBOSE]] verbose:acceptor "dispatching request from accepted channel"
				result, except = self:processrequest(result)
			end
		end
	until not result or not self[accesspoint]                                     --[[VERBOSE]] verbose:acceptor(false)
	return result, except
end

function halt(self)                                                             --[[VERBOSE]] verbose:acceptor "halt acceptor"
	local accesspoint = self.accesspoint
	if self[accesspoint] then
		self[accesspoint] = nil
		return self.listener:freeaccess(accesspoint)
	else
		return nil, Exception{
			reason = "halt",
			message = "channels not being accepted",
		}
	end
end
