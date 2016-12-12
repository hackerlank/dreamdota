local ipairs  = ipairs
local require = require
local builder = require "oil.builder"
local arch    = require "oil.arch.basic.client"

module "oil.builder.basic.client"

ProxyManager = arch.ProxyManager{require "oil.kernel.base.Proxies"}

function create(comps)
	comps = comps or {}
	comps.extraproxies = comps.extraproxies or {"asynchronous", "protected"}
	
	if comps.ProxyManager == nil then
		local proxykind = comps.proxykind or "synchronous"
		comps.ProxyManager = ProxyManager{
			invoker = require("oil.kernel.base.Proxies."..proxykind),
		}
		comps.extraproxies[proxykind] = comps.ProxyManager
	end
	
	for _, proxykind in ipairs(comps.extraproxies) do
		if comps.extraproxies[proxykind] == nil then
			comps.extraproxies[proxykind] = ProxyManager{
				invoker = require("oil.kernel.base.Proxies."..proxykind),
			}
		end
	end
	
	return comps
end
