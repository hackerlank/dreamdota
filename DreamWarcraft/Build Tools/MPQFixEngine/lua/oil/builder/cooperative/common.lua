local require = require
local builder = require "oil.builder"
local arch    = require "oil.arch.cooperative.common"

module "oil.builder.cooperative.common"

BasicSystem = arch.BasicSystem{require "loop.thread.SocketScheduler"}

function create(comps)
	return builder.create(_M, comps)
end
