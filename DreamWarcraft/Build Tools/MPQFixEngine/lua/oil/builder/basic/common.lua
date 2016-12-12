local require = require
local builder = require "oil.builder"
local arch    = require "oil.arch.basic.common"

module "oil.builder.basic.common"

BasicSystem = arch.BasicSystem{require "oil.kernel.base.Sockets"}

function create(comps)
	return builder.create(_M, comps)
end
