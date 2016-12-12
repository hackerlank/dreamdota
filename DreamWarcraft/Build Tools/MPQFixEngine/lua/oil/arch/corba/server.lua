local pairs = pairs

local port      = require "oil.port"
local component = require "oil.component"
local arch      = require "oil.arch"                                            --[[VERBOSE]] local verbose = require "oil.verbose"

module "oil.arch.corba.server"

RequestListener = component.Template{
	requests = port.Facet,
	codec    = port.Receptacle,
	servants = port.Receptacle,
	channels = port.HashReceptacle,
}

function assemble(components)
	arch.start(components)
	
	-- GIOP MAPPINGS
	local IOPServerChannels  = { [0] = ServerChannels }
	
	-- LISTENER
	RequestListener.codec    = CDREncoder.codec
	RequestListener.servants = ServantManager.servants
	RequestListener.indexer  = TypeRepository.indexer
	RequestListener.pcall    = BasicSystem.pcall -- to catch marshal errors
	
	-- COMMUNICATION
	for tag, ServerChannels in pairs(IOPServerChannels) do
		ServerChannels.sockets        = BasicSystem.sockets
		RequestListener.channels[tag] = ServerChannels.channels
	end
	
	arch.finish(components)
end
