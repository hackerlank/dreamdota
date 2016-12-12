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
-- Title  : Socket API Wrapper                                                --
-- Authors: Renato Maia <maia@inf.puc-rio.br>                                 --
--------------------------------------------------------------------------------

local luapcall = pcall

local socket = require "socket.core"

local oo = require "oil.oo"

module("oil.kernel.base.Sockets", oo.class)

pcall = luapcall

function __index(self, field)
	return _M[field] or socket[field]
end

function select(self, recvt, sendt, timeout)
	return socket.select(recvt, sendt, timeout)
end

function sleep(self, timeout)
	return socket.sleep(timeout)
end

function tcp(self)
	return socket.tcp()
end

function udp(self)
	return socket.udp()
end
