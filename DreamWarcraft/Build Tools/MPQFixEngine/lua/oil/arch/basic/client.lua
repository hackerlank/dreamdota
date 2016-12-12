local ipairs = ipairs

local port      = require "oil.port"
local component = require "oil.component"
local arch      = require "oil.arch"

module "oil.arch.basic.client"

ProxyManager = component.Template{
	proxies   = port.Facet,
	requester = port.Receptacle,
	referrer  = port.Receptacle,
	servants  = port.Receptacle,
}

function assemble(components)
	arch.start(components)
	ProxyManager.requester = OperationRequester.requests
	ProxyManager.referrer  = ObjectReferrer.references
	ProxyManager.servants  = ServantManager.servants
	
	for _, proxykind in ipairs(extraproxies) do
		local ProxyManager = extraproxies[proxykind]
		ProxyManager.requester = OperationRequester.requests
		ProxyManager.referrer  = ObjectReferrer.references
		ProxyManager.servants  = ServantManager.servants
	end
	arch.finish(components)
end
