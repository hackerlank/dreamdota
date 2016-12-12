local ipairs = ipairs

local port      = require "oil.port"
local component = require "oil.component"
local arch      = require "oil.arch"
local base      = require "oil.arch.basic.client"

module "oil.arch.typed.client"

ProxyManager = component.Template({
	types   = port.Receptacle,
	indexer = port.Receptacle,
	caches  = port.Facet, -- TODO:[maia] use it to reset method cache when type
}, base.ProxyManager)   --             definition changes.

function assemble(components)
	arch.start(components)
	ProxyManager.indexer = TypeRepository.indexer
	ProxyManager.types   = TypeRepository.types
	
	for _, proxykind in ipairs(extraproxies) do
		local ProxyManager = extraproxies[proxykind]
		ProxyManager.indexer = TypeRepository.indexer
		ProxyManager.types   = TypeRepository.types
	end
	arch.finish(components)
end
