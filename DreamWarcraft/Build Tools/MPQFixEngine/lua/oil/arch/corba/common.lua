local pairs = pairs

local port      = require "oil.port"
local component = require "oil.component"
local arch      = require "oil.arch"
local base      = require "oil.arch.typed.common"
local sysex     = require "oil.corba.idl.sysex"                                 --[[VERBOSE]] local verbose = require "oil.verbose"

module "oil.arch.corba.common"

-- TYPES
TypeRepository = component.Template({
	registry  = port.Facet,
	compiler  = port.Facet,
	delegated = port.Receptacle,
}, base.TypeRepository)

-- MARSHALING
ValueEncoder = component.Template{
	codec    = port.Facet,
	proxies  = port.Receptacle,
	servants = port.Receptacle,
	types    = port.Receptacle,
}

-- REFERENCES
ReferenceProfiler = component.Template{
	profiler = port.Facet,
	codec    = port.Receptacle,
}
ObjectReferrer = component.Template{
	references = port.Facet,
	codec      = port.Receptacle,
	requester  = port.Receptacle,
	profiler   = port.HashReceptacle,
}

function assemble(components)
	arch.start(components)
	
	-- IDL DEFINITIONS
	TypeRepository.types:register(sysex)
	
	-- MARSHALING
	CDREncoder.proxies   = ProxyManager.proxies
	CDREncoder.servants  = ServantManager.servants
	CDREncoder.types     = TypeRepository.types

	-- REFERENCES
	ObjectReferrer.codec      = CDREncoder.codec
	ObjectReferrer.servants   = ServantManager.servants
	for tag, IORProfiler in pairs(IORProfilers) do
		IORProfiler.codec            = CDREncoder.codec
		ObjectReferrer.profiler[tag] = IORProfiler.profiler
	end
	
	arch.finish(components)
end
