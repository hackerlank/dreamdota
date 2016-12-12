local port      = require "oil.port"
local component = require "oil.component"
local arch      = require "oil.arch"
local base      = require "oil.arch.basic.server"

module "oil.arch.typed.server"

ServantManager = component.Template({
	types   = port.Receptacle,
	indexer = port.Receptacle,
}, base.ServantManager)

function assemble(components)
	arch.start(components)
	ServantManager.indexer = TypeRepository.indexer
	ServantManager.types   = TypeRepository.types
	arch.finish(components)
end
