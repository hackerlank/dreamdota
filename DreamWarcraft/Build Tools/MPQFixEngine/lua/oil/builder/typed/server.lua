local require = require
local builder = require "oil.builder"
local arch    = require "oil.arch.typed.server"

module "oil.builder.typed.server"

ServantManager = arch.ServantManager{require "oil.kernel.typed.Servants"  ,
                        dispatcher = require "oil.kernel.typed.Dispatcher"}

function create(comps)
	return builder.create(_M, comps)
end
