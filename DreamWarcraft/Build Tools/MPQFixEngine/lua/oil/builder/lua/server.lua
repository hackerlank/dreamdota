local require = require
local builder = require "oil.builder"
local arch    = require "oil.arch.basic.server"

module "oil.builder.lua.server"

ServantManager = arch.ServantManager {require "oil.kernel.base.Servants",
                         dispatcher = require "oil.kernel.lua.Dispatcher"}

function create(comps)
	return builder.create(_M, comps)
end
