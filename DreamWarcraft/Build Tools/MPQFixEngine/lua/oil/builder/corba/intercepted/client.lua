local require = require
local builder = require "oil.builder"
local arch    = require "oil.arch.corba.intercepted.client"

module "oil.builder.corba.intercepted.client"

OperationRequester = arch.OperationRequester{require "oil.corba.intercepted.Requester" }

function create(comps)
	return builder.create(_M, comps)
end
