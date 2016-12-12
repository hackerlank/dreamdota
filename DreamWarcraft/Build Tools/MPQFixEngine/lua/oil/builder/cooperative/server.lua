local require = require
local builder = require "oil.builder"
local arch    = require "oil.arch.cooperative.server"

module "oil.builder.cooperative.server"

RequestReceiver = arch.RequestReceiver{require "oil.kernel.cooperative.Receiver"}

function create(comps)
	return builder.create(_M, comps)
end
