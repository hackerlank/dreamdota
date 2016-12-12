local pairs = pairs

local port      = require "oil.port"
local component = require "oil.component"
local arch      = require "oil.arch"                                            --[[VERBOSE]] local verbose = require "oil.verbose"

module "oil.arch.corba.client"

OperationRequester = component.Template{
	requests  = port.Facet,
	codec     = port.Receptacle,
	profiler  = port.HashReceptacle,
	channels  = port.HashReceptacle,
}

function assemble(components)
	arch.start(components)
	
	-- GIOP MAPPINGS
	local IOPClientChannels  = { [0] = ClientChannels }
	
	-- REQUESTER
	OperationRequester.codec = CDREncoder.codec
	OperationRequester.pcall = BasicSystem.pcall -- to catch marshal errors

	-- COMMUNICATION
	for tag, ClientChannels in pairs(IOPClientChannels) do
		ClientChannels.sockets           = BasicSystem.sockets
		OperationRequester.channels[tag] = ClientChannels.channels
	end
	
	-- REFERENCES
	ObjectReferrer.requester  = OperationRequester.requests
	for tag, IORProfiler in pairs(IORProfilers) do
		OperationRequester.profiler[0] = IIOPProfiler
	end
	
	arch.finish(components)
end
