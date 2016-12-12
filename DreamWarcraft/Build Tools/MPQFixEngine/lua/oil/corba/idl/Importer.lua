--------------------------------------------------------------------------------
------------------------------  #####      ##     ------------------------------
------------------------------ ##   ##  #  ##     ------------------------------
------------------------------ ##   ## ##  ##     ------------------------------
------------------------------ ##   ##  #  ##     ------------------------------
------------------------------  #####  ### ###### ------------------------------
--------------------------------                --------------------------------
----------------------- An Object Request Broker in Lua ------------------------
--------------------------------------------------------------------------------
-- Project: OiL - ORB in Lua: An Object Request Broker in Lua                 --
-- Release: 0.5                                                               --
-- Title  : IDL Definition Repository                                         --
-- Authors: Renato Maia <maia@inf.puc-rio.br>                                 --
--------------------------------------------------------------------------------
-- importer:Facet
-- 	type:table register(definition:table)
-- 	type:table remove(definition:table)
-- 	[type:table] lookup(name:string)
-- 	[type:table] lookup_id(repid:string)
-- 
-- registry:Receptacle
-- 	type:table register(definition:table)
-- 	type:table remove(definition:table)
-- 	[type:table] lookup(name:string)
-- 	[type:table] lookup_id(repid:string)
-- 
-- delegated:Recetacle
-- 	[type:table] lookup(name:string)
-- 	[type:table] lookup_id(repid:string)
------------------------------------------------------------------------------ --

local error  = error
local ipairs = ipairs
local pairs  = pairs
local type   = type

local oo       = require "oil.oo"
local idl      = require "oil.corba.idl"
local iridl    = require "oil.corba.idl.ir"
local Registry = require "oil.corba.idl.Registry"                               --[[VERBOSE]] local verbose = require "oil.verbose"

module "oil.corba.idl.Importer"

oo.class(_M, Registry)

function context(self, context)
	self.context = context
	local registry = context.__component
	registry:register(iridl)
	self.DefaultDefs = oo.class()
	for id, def in pairs(registry.definition_map) do
		self.DefaultDefs[id] = def
	end
end

function lookup(self, search_name)
	local context = self.context
	local definition = context.__component:lookup(search_name)
	if not definition then
		if context.delegated then
			definition = context.delegated:lookup(search_name)
			if definition then
				definition = self:register(definition)
			end
		end
	end
	return definition
end

function lookup_id(self, search_id)
	local context = self.context
	local definition = context.__component:lookup_id(search_id)
	if not definition then
		if context.delegated then
			definition = context.delegated:lookup_id(search_id)
			if definition then
				definition = self:register(definition)
			end
		end
	end
	return definition
end

local IDLTypes = {
	dk_Primitive = true,
	dk_String    = true,
	dk_Array     = true,
	dk_Sequence  = true,
}

local Contained = {
	dk_Alias             = { const = idl.typedef,            iface = "IDL:omg.org/CORBA/AliasDef:1.0"             },
	dk_Enum              = { const = idl.enum,               iface = "IDL:omg.org/CORBA/EnumDef:1.0"              },
	dk_Struct            = { const = idl.struct,             iface = "IDL:omg.org/CORBA/StructDef:1.0"            },
	dk_Union             = { const = idl.union,              iface = "IDL:omg.org/CORBA/UnionDef:1.0"             },
	dk_Exception         = { const = idl.except,             iface = "IDL:omg.org/CORBA/ExceptionDef:1.0"         },
	dk_Module            = { const = idl.module,             iface = "IDL:omg.org/CORBA/ModuleDef:1.0"            },
	dk_Interface         = { const = idl.interface,          iface = "IDL:omg.org/CORBA/InterfaceDef:1.0"         },
	dk_AbstractInterface = { const = idl.abstract_interface, iface = "IDL:omg.org/CORBA/AbstractInterfaceDef:1.0" },
	dk_LocalInterface    = { const = idl.local_interface,    iface = "IDL:omg.org/CORBA/LocalInterfaceDef:1.0"    },
	dk_Attribute         = { const = idl.attribute,          iface = "IDL:omg.org/CORBA/AttributeDef:1.0"         },
	dk_Operation         = { const = idl.operation,          iface = "IDL:omg.org/CORBA/OperationDef:1.0"         },
	dk_ValueBox          = { const = idl.valuebox ,          iface = "IDL:omg.org/CORBA/ValueBoxDef:1.0"          },
	dk_Value             = { const = idl.valuetype,          iface = "IDL:omg.org/CORBA/ValueDef:1.0"             },
	dk_ValueMember       = { const = idl.valuemember,        iface = "IDL:omg.org/CORBA/ValueMemberDef:1.0"       },
}

function register(self, object, history)
	local result
	local registry = self.context.__component
	if object._get_def_kind then -- is a remote definition
		local kind = object:_get_def_kind()
		if kind == "dk_Repository" then
			result = registry
		elseif IDLTypes[kind] then
			local desc
			-- import definition specific information
			if kind == "dk_Array" then
				object = object:_narrow("IDL:omg.org/CORBA/ArrayDef:1.0")
				desc = object:_get_type()
				desc.elementtype = self:register(object:_get_element_type_def(), history)
			elseif kind == "dk_Sequence" then
				object = object:_narrow("IDL:omg.org/CORBA/SequenceDef:1.0")
				desc = object:_get_type()
				desc.elementtype = self:register(object:_get_element_type_def(), history)
			else
				object = object:_narrow("IDL:omg.org/CORBA/IDLType:1.0")
				desc = object:_get_type()
			end
			result = registry:register(desc)
		elseif Contained[kind] then
			object = object:_narrow(Contained[kind].iface)
			local desc = object:describe().value
			history = history or self.DefaultDefs()
			result = history[desc.id] or registry:lookup_id(desc.id)
			if not result then                                                        --[[VERBOSE]] verbose:repository(true, "importing definition ",desc.id)
				desc.repID = desc.id
				desc.defined_in = nil
				
				-- import definition specific information
				if kind == "dk_Enum" then
					desc.enumvalues = object:_get_members()
				elseif kind == "dk_Union" then
					desc.switch = self:register(object:_get_discriminator_type_def(), history)
				elseif kind == "dk_Alias" or kind == "dk_ValueBox" then
					desc.original_type = self:register(object:_get_original_type_def(), history)
				elseif kind == "dk_Attribute" or  kind == "dk_ValueMember" then
					desc.type = self:register(object:_get_type_def(), history)
				elseif kind == "dk_Operation" then
					desc.result = self:register(object:_get_result_def(), history)
					local params = desc.parameters
					for _, param in ipairs(params) do
						param.type = self:register(param.type_def, history)
					end
					local excepts = object:_get_exceptions()
					desc.exceptions = {}
					for index, except in ipairs(excepts) do
						desc.exceptions[index] = self:register(except, history)
					end
				elseif kind == "dk_Value" then
					desc.base_value = nil
					desc.abstract_base_values = nil
					desc.abstract = desc.is_abstract
					desc.trucatable = desc.is_trucatable
					desc.custom = desc.is_custom
				elseif kind == "dk_Interface" or kind == "dk_AbstractInterface" then
					desc.base_interfaces = nil
				end
				
				-- registration of the imported definition
				result = registry:register(Contained[kind].const(desc))                 --[[VERBOSE]] verbose:repository("definition ",desc.id," registered")
				history[result.repID] = result
				
				-- import definition specific information
				if kind == "dk_Interface" or kind == "dk_AbstractInterface" then
					local bases = object:_get_base_interfaces()
					for index, base in ipairs(bases) do
						bases[index] = self:register(base, history)
					end
					result:_set_base_interfaces(bases)
				elseif kind == "dk_Value" then
					local base = object:_get_base_value()
					if base then
						result:_set_base_value(self:register(base, history))
					end
					local bases = object:_get_abstract_base_values()
					for index, base in ipairs(bases) do
						bases[index] = self:register(base, history)
					end
					result:_set_abstract_base_values(bases)
					local ifaces = object:_get_supported_interfaces()
					for index, iface in ipairs(ifaces) do
						ifaces[index] = self:register(iface, history)
					end
					result:_set_supported_interfaces(ifaces)
				elseif kind == "dk_Struct" or kind == "dk_Union" or kind == "dk_Exception" then
					local members = object:_get_members()
					for _, member in ipairs(members) do
						member.type = self:register(member.type_def, history)
						member.type_def = member.type
					end
					if result._set_members
						then result:_set_members(members)
						else result.members = members
					end
				end
				
				-- resolve contaiment
				result:move(
					self:register(object:_get_defined_in(), history),
					result.name,
					result.version
				)
				if object.contents then
					for _, contained in ipairs(object:contents("dk_all", true)) do
						self:register(contained, history)
					end
				end                                                                     --[[VERBOSE]] verbose:repository(false)
			end
		else
			error("unable to import definition of type "..object:_interface():_get_id())
		end
	else -- a local IDL description
		result = registry:register(object)
	end
	return result
end

function resolve(self, typeref)
	if type(typeref) == "table" and typeref.__reference then
		return self:register(typeref)
	else
		return Registry.resolve(self, typeref)
	end
end
