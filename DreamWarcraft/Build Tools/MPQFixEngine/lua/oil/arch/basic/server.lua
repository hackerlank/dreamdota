local port      = require "oil.port"
local component = require "oil.component"
local arch      = require "oil.arch"                                            --[[VERBOSE]] local verbose = require "oil.verbose"

module "oil.arch.basic.server"

ServantManager = component.Template{
	servants   = port.Facet,
	dispatcher = port.Facet,
	referrer   = port.Receptacle,
}
RequestReceiver = component.Template{
	acceptor   = port.Facet,
	dispatcher = port.Receptacle,
	listener   = port.Receptacle,
}

function assemble(components)
	arch.start(components)
	ServantManager.referrer    = ObjectReferrer.references
	RequestReceiver.dispatcher = ServantManager.dispatcher
	RequestReceiver.listener   = RequestListener.requests
	
	-- define 'pcall' used in invocation dispatching.
	ServantManager.dispatcher.pcall = BasicSystem.pcall
	arch.finish(components)
end
