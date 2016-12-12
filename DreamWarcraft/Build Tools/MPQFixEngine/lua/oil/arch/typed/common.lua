local port      = require "oil.port"
local component = require "oil.component"

module "oil.arch.typed.common"

TypeRepository = component.Template{
	types   = port.Facet,
	indexer = port.Facet,
}
