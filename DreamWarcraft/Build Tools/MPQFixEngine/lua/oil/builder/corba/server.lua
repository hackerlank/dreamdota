local require = require
local builder = require "oil.builder"
local base    = require "oil.arch.basic.common"
local arch    = require "oil.arch.corba.server"

module "oil.builder.corba.server"

ServerChannels  = base.SocketChannels {require "oil.kernel.base.Acceptor"}
RequestListener = arch.RequestListener{require "oil.corba.giop.Listener" }

function create(comps)
	return builder.create(_M, comps)
end
