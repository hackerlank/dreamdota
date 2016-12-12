local port      = require "oil.port"
local component = require "oil.component"
local arch      = require "oil.arch"

module "oil.arch.ludo.client"

OperationRequester = component.Template{
	requests = port.Facet,
	channels = port.Receptacle,
	codec    = port.Receptacle,
}

function assemble(components)
	arch.start(components)
	ClientChannels.sockets      = BasicSystem.sockets
	OperationRequester.codec    = LuaEncoder.codec
	OperationRequester.channels = ClientChannels.channels
	arch.finish(components)
end
