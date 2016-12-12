local require = require
local builder = require "oil.builder"
local base    = require "oil.arch.basic.common"
local arch    = require "oil.arch.corba.client"

module "oil.builder.corba.client"

ClientChannels     = base.SocketChannels    {require "oil.kernel.base.Connector"}
OperationRequester = arch.OperationRequester{require "oil.corba.giop.Requester" }

function create(comps)
	return builder.create(_M, comps)
end
