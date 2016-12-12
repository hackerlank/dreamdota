local require = require
local builder = require "oil.builder"
local arch    = require "oil.arch.ludo.common"

module "oil.builder.ludo.common"

LuaEncoder     = arch.ValueEncoder  {require "oil.ludo.Codec"   }
ObjectReferrer = arch.ObjectReferrer{require "oil.ludo.Referrer"}

function create(comps)
	comps = builder.create(_M, comps)
	comps.ValueEncoder = comps.LuaEncoder
	return comps
end
