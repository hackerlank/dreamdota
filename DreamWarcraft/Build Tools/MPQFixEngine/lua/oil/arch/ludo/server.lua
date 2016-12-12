local port      = require "oil.port"
local component = require "oil.component"
local arch      = require "oil.arch"

module "oil.arch.ludo.server"

RequestListener = component.Template{
	requests = port.Facet,
	channels = port.Receptacle,
	codec    = port.Receptacle,
}

function assemble(components)
	arch.start(components)
	ServerChannels.sockets   = BasicSystem.sockets
	RequestListener.codec    = LuaEncoder.codec
	RequestListener.channels = ServerChannels.channels
	arch.finish(components)
end
