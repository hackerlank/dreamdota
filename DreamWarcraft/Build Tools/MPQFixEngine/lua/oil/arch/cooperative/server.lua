local port      = require "oil.port"
local component = require "oil.component"
local arch      = require "oil.arch"
local base      = require "oil.arch.basic.server"                                --[[VERBOSE]] local verbose = require "oil.verbose"

module "oil.arch.cooperative.server"

RequestReceiver = component.Template({
	tasks = port.Receptacle,
}, base.RequestReceiver)

function assemble(components)
	arch.start(components)
	RequestReceiver.tasks  = BasicSystem.tasks
	arch.finish(components)
end
