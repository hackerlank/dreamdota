local setfenv = setfenv
local require = require
local builder = require "oil.builder"
local arch    = require "oil.arch.typed.client"
local basic   = require "oil.builder.basic.client"

module "oil.builder.typed.client"

ProxyManager = arch.ProxyManager{require "oil.kernel.typed.Proxies"}

function create(comps)
	setfenv(basic.create, _M)
	comps = basic.create(comps)
	setfenv(basic.create, basic)
	return comps
end
