local require = require
local builder = require "oil.builder"
local arch    = require "oil.arch.ludo.byref"

module "oil.builder.ludo.byref"

LuaEncoder = arch.ValueEncoder{require "oil.ludo.CodecByRef"}

function create(comps)
	comps = builder.create(_M, comps)
	comps.ValueEncoder = comps.LuaEncoder
	return comps
end
