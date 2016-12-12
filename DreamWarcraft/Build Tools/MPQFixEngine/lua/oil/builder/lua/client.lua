local require = require
local builder = require "oil.builder"
local arch    = require "oil.arch.basic.client"

module "oil.builder.lua.client"

ProxyManager = arch.ProxyManager{require "oil.kernel.lua.Proxies"}

function create(comps)
	return builder.create(_M, comps)
end
