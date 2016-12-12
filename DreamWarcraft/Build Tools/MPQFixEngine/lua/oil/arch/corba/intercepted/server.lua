local port = require "oil.port"
local comp = require "oil.component"
local base = require "oil.arch.corba.server"

module "oil.arch.corba.intercepted.server"

RequestListener = comp.Template({
	interceptor = port.Receptacle,
}, base.RequestListener)
