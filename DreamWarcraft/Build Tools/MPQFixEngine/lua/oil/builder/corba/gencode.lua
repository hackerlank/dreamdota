local require = require
local builder = require "oil.builder"
local arch    = require "oil.arch.corba.common"

module "oil.builder.corba.gencode"

CDREncoder = arch.ValueEncoder{require "oil.corba.giop.CodecGen"  }

function create(comps)
	comps = builder.create(_M, comps)
	comps.ValueEncoder = comps.CDREncoder
	return comps
end
