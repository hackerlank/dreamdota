local require = require
local builder = require "oil.builder"
local base    = require "oil.arch.basic.common"
local arch    = require "oil.arch.ludo.client"

module "oil.builder.ludo.client"

ClientChannels     = base.SocketChannels    {require "oil.kernel.base.Connector"}
OperationRequester = arch.OperationRequester{require "oil.ludo.Requester"       }

function create(comps)
	return builder.create(_M, comps)
end
