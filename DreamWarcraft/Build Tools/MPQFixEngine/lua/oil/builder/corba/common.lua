local require = require
local builder = require "oil.builder"
local arch    = require "oil.arch.corba.common"

module "oil.builder.corba.common"

IIOPProfiler    = arch.ReferenceProfiler{require "oil.corba.iiop.Profiler"}
CDREncoder      = arch.ValueEncoder     {require "oil.corba.giop.Codec"   }
ObjectReferrer  = arch.ObjectReferrer   {require "oil.corba.giop.Referrer"}
TypeRepository  = arch.TypeRepository   {require "oil.corba.idl.Registry" ,
                              indexer  = require "oil.corba.giop.Indexer" ,
                              compiler = require "oil.corba.idl.Compiler" ,
                              types    = require "oil.corba.idl.Importer" }

function create(comps)
	comps = builder.create(_M, comps)
	comps.IORProfilers = {
		[0]  = comps.IIOPProfiler,
		[""] = comps.IIOPProfiler,
		iiop = comps.IIOPProfiler,
	}
	comps.ValueEncoder = comps.CDREncoder
	return comps
end
