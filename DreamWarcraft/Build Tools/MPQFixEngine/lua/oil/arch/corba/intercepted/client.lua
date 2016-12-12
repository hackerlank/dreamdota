local port = require "oil.port"
local comp = require "oil.component"
local base = require "oil.arch.corba.client"

module "oil.arch.corba.intercepted.client"

OperationRequester = comp.Template({
	interceptor = port.Receptacle
}, base.OperationRequester)
