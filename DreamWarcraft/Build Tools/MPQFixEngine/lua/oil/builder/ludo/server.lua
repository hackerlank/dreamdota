local require = require
local builder = require "oil.builder"
local base    = require "oil.arch.basic.common"
local arch    = require "oil.arch.ludo.server"

module "oil.builder.ludo.server"

ServerChannels  = base.SocketChannels {require "oil.kernel.base.Acceptor"}
RequestListener = arch.RequestListener{require "oil.ludo.Listener"       }

function create(comps)
	return builder.create(_M, comps)
end
