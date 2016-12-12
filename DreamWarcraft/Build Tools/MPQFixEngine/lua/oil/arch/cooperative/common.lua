local port      = require "oil.port"
local component = require "oil.component"
local base      = require "oil.arch.basic.common"                               --[[VERBOSE]] local verbose = require "oil.verbose"

module "oil.arch.cooperative.common"

BasicSystem = component.Template({
	control = port.Facet,
	tasks   = port.Facet,
}, base.BasicSystem)
