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
-- Title  : Mapping of Lua values into Common Data Representation (CDR)       --
-- Authors: Renato Maia <maia@inf.puc-rio.br>                                 --
--------------------------------------------------------------------------------
-- decoder interface:                                                         --
--   order(value)    Change or return the endianess of the buffer             --
--   jump(shift)     Places an empty space in the data of the buffer          --
--   getdata()       Returns the raw data stream of marshalled data           --
--   get(type)       Unmarhsall a value of the given type                     --
--                                                                            --
--   void()          Unmarshal a void type value                              --
--   short()         Unmarshal an integer type short value                    --
--   long()          Unmarshal an integer type long value                     --
--   ushort()        Unmarshal an integer type unsigned short value           --
--   ulong()         Unmarshal an integer type unsigned long value            --
--   float()         Unmarshal a floating-point numeric type value            --
--   double()        Unmarshal a double-precision floating-point num. value   --
--   boolean()       Unmarshal a boolean type value                           --
--   char()          Unmarshal a character type value                         --
--   octet()         Unmarshal a raw byte type value                          --
--   any()           Unmarshal a generic type value                           --
--   TypeCode()      Unmarshal a meta-type value                              --
--   string()        Unmarshal a string type value                            --
--                                                                            --
--   Object(type)    Unmarhsal an Object type value, given its type           --
--   struct(type)    Unmarhsal a struct type value, given its type            --
--   union(type)     Unmarhsal a union type value, given its type             --
--   enum(type)      Unmarhsal an enumeration type value, given its type      --
--   sequence(type)  Unmarhsal a sequence type value, given its type          --
--   array(type)     Unmarhsal an array type value, given its type            --
--   typedef(type)   Unmarhsal a type definition value, given its type        --
--   except(type)    Unmarhsal an expection value, given its type             --
--                                                                            --
--   interface(type) Unmarshall an object reference of a given interface      --
--                                                                            --
-- encoder interface:                                                         --
--   order(value)         Change or return the endianess of the buffer        --
--   jump(shift)          Jump an empty space in the data of the buffer       --
--   getdata()            Returns the raw data stream of marshalled data      --
--   put(type)            Marhsall a value of the given type                  --
--                                                                            --
--   void(value)          Marshal a void type value                           --
--   short(value)         Marshal an integer type short value                 --
--   long(value)          Marshal an integer type long value                  --
--   ushort(value)        Marshal an integer type unsigned short value        --
--   ulong(value)         Marshal an integer type unsigned long value         --
--   float(value)         Marshal a floating-point numeric type value         --
--   double(value)        Marshal a double-prec. floating-point num. value    --
--   boolean(value)       Marshal a boolean type value                        --
--   char(value)          Marshal a character type value                      --
--   octet(value)         Marshal a raw byte type value                       --
--   any(value)           Marshal a generic type value                        --
--   TypeCode(value)      Marshal a meta-type value                           --
--   string(value)        Marshal a string type value                         --
--                                                                            --
--   Object(value, type)  Marhsal an Object type value, given its type        --
--   struct(value, type)  Marhsal a struct type value, given its type         --
--   union(value, type)   Marhsal an union type value, given its type         --
--   enum(value, type)    Marhsal an enumeration type value, given its type   --
--   sequence(value, type)Marhsal a sequence type value, given its type       --
--   array(value, type)   Marhsal an array type value, given its type         --
--   typedef(value, type) Marhsal a type definition value, given its type     --
--   except(value, type)  Marhsal an expection value, given its type          --
--                                                                            --
--   interface(value,type)Marshall an object reference of a given interface   --
--------------------------------------------------------------------------------
-- Notes:                                                                     --
--   See section 15.3 of CORBA 3.0 specification.                             --
--------------------------------------------------------------------------------
-- codec:Facet
-- 	encoder:object encoder()
-- 	decoder:object decoder(stream:string)
-- 
-- proxies:Receptacle
-- 	proxy:object proxyto(ior:table, iface:table|string)
-- 
-- servants:Receptacle
-- 	proxy:object register(implementation:object, iface:table|string)
--------------------------------------------------------------------------------

local getmetatable = getmetatable
local ipairs       = ipairs
local pairs        = pairs
local pcall        = pcall
local rawget       = rawget
local setmetatable = setmetatable
local tonumber     = tonumber
local type         = type

local math   = require "math"
local string = require "string"
local table  = require "table"

local oo     = require "oil.oo"
local assert = require "oil.assert"
local bit    = require "oil.bit"
local idl    = require "oil.corba.idl"
local giop   = require "oil.corba.giop"                                         --[[VERBOSE]] local verbose = require "oil.verbose"; local CURSOR, CODEC, PREFIXSHIFT, SIZEINDEXPOS, verbose_marshal, verbose_unmarshal = {}

module("oil.corba.giop.Codec", oo.class)

local IndirectionTag = 0xffffffff

--------------------------------------------------------------------------------
--------------------------------------------------------------------------------

UnionLabelInfo = { name = "label", type = idl.void }

--------------------------------------------------------------------------------
-- TypeCode information --------------------------------------------------------

-- NOTE: Description of type code categories, which is defined by field type
--	empty  : no further parameters are necessary to specify the associated
--           type.
--	simple : parameters that specify the associated type are defined as a
--           sequence of values.
--	complex: parameters that specify the associated type are defined as a
--           structure defined in idl that is stored in a encapsulated octet
--           sequence (i.e. which endianess may differ).

TypeCodeInfo = {
	[0]  = {name = "null"     , type = "empty", idl = idl.null     }, 
	[1]  = {name = "void"     , type = "empty", idl = idl.void     }, 
	[2]  = {name = "short"    , type = "empty", idl = idl.short    },
	[3]  = {name = "long"     , type = "empty", idl = idl.long     },
	[4]  = {name = "ushort"   , type = "empty", idl = idl.ushort   },
	[5]  = {name = "ulong"    , type = "empty", idl = idl.ulong    },
	[6]  = {name = "float"    , type = "empty", idl = idl.float    },
	[7]  = {name = "double"   , type = "empty", idl = idl.double   },
	[8]  = {name = "boolean"  , type = "empty", idl = idl.boolean  },
	[9]  = {name = "char"     , type = "empty", idl = idl.char     },
	[10] = {name = "octet"    , type = "empty", idl = idl.octet    },
	[11] = {name = "any"      , type = "empty", idl = idl.any      },
	[12] = {name = "TypeCode" , type = "empty", idl = idl.TypeCode },
	[13] = {name = "Principal", type = "empty", idl = idl.Principal, unhandled = true},

	[14] = {name = "Object", type = "complex",
		parameters = idl.struct{
			{name = "repID", type = idl.string},
			{name = "name" , type = idl.string},
		},
	},
	[15] = {name = "struct", type = "complex",
		parameters = idl.struct{
			{name = "repID" , type = idl.string},
			{name = "name"  , type = idl.string},
			{name = "fields", type = idl.sequence{
				idl.struct{
					{name = "name", type = idl.string},
					{name = "type", type = idl.TypeCode}
				},
			}},
		},
	},
	[16] = {name = "union", type = "complex",
		parameters = idl.struct{
			{name = "repID"  , type = idl.string  },
			{name = "name"   , type = idl.string  },
			{name = "switch" , type = idl.TypeCode},
			{name = "default", type = idl.long    },
		},
		mutable = {
			{name = "options", type = idl.sequence{
				idl.struct{
					UnionLabelInfo, -- NOTE: depends on field 'switch'.
					{name = "name" , type = idl.string  },
					{name = "type" , type = idl.TypeCode},
				},
			}},
			setup = function(self, union)
				UnionLabelInfo.type = union.switch
				return self
			end,
		},
	},
	[17] = {name = "enum", type = "complex",
		parameters = idl.struct{
			{name = "repID"     , type = idl.string              },
			{name = "name"      , type = idl.string              },
			{name = "enumvalues", type = idl.sequence{idl.string}},
		}
	},
	[18] = {name = "string", type = "simple", idl = idl.string,
		parameters = idl.struct{
			{name = "maxlength", type = idl.ulong}
		},
	},
	[19] = {name = "sequence", type = "complex",
		parameters = idl.struct{
			{name = "elementtype", type = idl.TypeCode},
			{name = "maxlength"  , type = idl.ulong   },
		}
	},
	[20] = {name = "array", type = "complex",
		parameters = idl.struct{
			{name = "elementtype", type = idl.TypeCode},
			{name = "length"     , type = idl.ulong   },
		}
		},
	[21] = {name = "typedef", type = "complex",
		parameters = idl.struct{
			{name = "repID"        , type = idl.string  },
			{name = "name"         , type = idl.string  },
			{name = "original_type", type = idl.TypeCode},
		},
	},
	[22] = {name = "except", type = "complex",
		parameters = idl.struct{
			{name = "repID", type = idl.string},
			{name = "name",  type = idl.string},
			{name = "members", type = idl.sequence{
				idl.struct{
					{name = "name", type = idl.string  },
					{name = "type", type = idl.TypeCode},
				},
			}},
		},
	},
	
	[23] = {name = "longlong"  , type = "empty", idl = idl.longlong  }, 
	[24] = {name = "ulonglong" , type = "empty", idl = idl.ulonglong },
	[25] = {name = "longdouble", type = "empty", idl = idl.longdouble},
	[26] = {name = "wchar"     , type = "empty", unhandled = true},
	
	[27] = {name = "wstring", type = "simple", unhandled = true,
		parameters = idl.struct{
			{name = "maxlength", type = idl.ulong},
		},
	},
	[28] = {name = "fixed", type = "simple", unhandled = true,
		parameters = idl.struct{
			{name = "digits", type = idl.ushort},
			{name = "scale" , type = idl.short },
		},
	},
	
	[29] = {name = "valuetype", type = "complex",
		parameters = idl.struct{
			{name = "repID"     , type = idl.string  },
			{name = "name"      , type = idl.string  },
			{name = "kind"      , type = idl.short   },
			{name = "base_value", type = idl.TypeCode},
			{name = "members"   , type = idl.sequence{
				idl.struct{
					{name = "name"  , type = idl.string  },
					{name = "type"  , type = idl.TypeCode},
					{name = "access", type = idl.short   },
				},
			}},
		},
	},
	[30] = {name = "valuebox", type = "complex",
		parameters = idl.struct{
			{name = "repID"        , type = idl.string  },
			{name = "name"         , type = idl.string  },
			{name = "original_type", type = idl.TypeCode},
		},
	},
	[31] = {name = "native", type = "complex", unhandled = true,
		parameters = idl.struct{
			{name = "repID", type = idl.string  },
			{name = "name" , type = idl.string  },
		},
	},
	[32] = {name = "abstract_interface", type = "complex",
		parameters = idl.struct{
			{name = "repID", type = idl.string  },
			{name = "name" , type = idl.string  },
		},
	},
	[33] = {name = "local_interface", type = "complex",
		parameters = idl.struct{
			{name = "repID", type = idl.string  },
			{name = "name" , type = idl.string  },
		},
	},
	
	[IndirectionTag] = {name = "indirection marker", type = "fake"},
}

local PrimitiveSizes = {
	boolean    =  1,
	char       =  1,
	octet      =  1,
	short      =  2,
	long       =  4,
	longlong   =  8,
	ushort     =  2,
	ulong      =  4,
	ulonglong  =  8,
	float      =  4,
	double     =  8,
	longdouble = 16,
	enum       =  4,
}

--------------------------------------------------------------------------------
-- Local module functions ------------------------------------------------------

local function alignment(self, size)
	local extra = (self.cursor-1)%size
	if extra > 0 then return size-extra end
	return 0
end

NativeEndianess = (bit.endianess() == "little")

--------------------------------------------------------------------------------
--   ##   ##   #####   ######    ######  ##   ##   #####   ##       ##        --
--   ### ###  ##   ##  ##   ##  ##       ##   ##  ##   ##  ##       ##        --
--   #######  #######  ######    #####   #######  #######  ##       ##        --
--   ## # ##  ##   ##  ##   ##       ##  ##   ##  ##   ##  ##       ##        --
--   ##   ##  ##   ##  ##   ##  ######   ##   ##  ##   ##  #######  #######   --
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
-- Unmarshalling buffer class --------------------------------------------------

Encoder = oo.class {
	previousend = 0,
	index = 1,
	cursor = 1,
	emptychar = '\255', -- character used in buffer alignment
	pack = bit.pack,    -- use current platform native endianess
}

local function newhistory(history)
	return setmetatable(history or {}, { __index = function(self, field)
		local value = {}
		self[field] = value
		return value
	end })
end

function Encoder:__init(object)
	self = oo.rawnew(self, object)
	if self.history == nil then self.history = newhistory() end
	if self.format == nil then self.format = {} end
	return self
end

function Encoder:shift(shift)                                                   --[[VERBOSE]] PREFIXSHIFT = shift
	self.cursor = self.cursor + shift
end

function Encoder:jump(shift)
	if shift > 0 then self:rawput('"', self.emptychar:rep(shift), shift) end
end

function Encoder:align(size)
	local shift = alignment(self, size)
	if shift > 0 then self:jump(shift) end
end

function Encoder:rawput(format, data, size)                                     --[[VERBOSE]] CURSOR[self.cursor] = true; if CODEC == nil then CODEC = self end
	local index = self.index
	self.format[index] = format
	self[index] = data
	self.index = index+1
	self.cursor = self.cursor + size
end

function Encoder:put(value, idltype)
	local marshal = self[idltype._type]
	if not marshal then
		assert.illegal(idltype._type, "supported type", "MARSHAL")
	end
	return marshal(self, value, idltype)
end

function Encoder:indirection(marshal, value, ...)
	local history = self.history
	local previous = history[marshal][value]
	if previous then
		self:ulong(IndirectionTag)
		self:long(previous - (self.previousend+self.cursor))                        --[[VERBOSE]] verbose_marshal("indirection to "..((self.previousend+self.cursor)-previous).." bytes away (",(self.previousend+self.cursor),"-",previous,").")
	else
		local shift = alignment(self, PrimitiveSizes.ulong)
		history[marshal][value] = (self.previousend+self.cursor+shift)               --[[VERBOSE]] verbose_marshal("registering position at ",history[marshal][value]," for future indirection")
		marshal(self, value, ...)
	end
end

function Encoder:getdata()
	return self.pack(table.concat(self.format), self)
end

function Encoder:getlength()
	return self.cursor - 1
end

local NilEnabledTypes = {
	any = true,
	boolean = true,
	Object = true,
	interface = true,
	valuetype = true,
}

--------------------------------------------------------------------------------
-- Marshalling functions -------------------------------------------------------

local function numbermarshaller(size, format)
	return function (self, value)
		assert.type(value, "number", "numeric value", "MARSHAL")
		self:align(size)
		self:rawput(format, value, size)                                            --[[VERBOSE]] verbose_marshal(self, format, value)
	end
end

Encoder.null       = function() end
Encoder.void       = Encoder.null
Encoder.short      = numbermarshaller(PrimitiveSizes.short     , "s")
Encoder.long       = numbermarshaller(PrimitiveSizes.long      , "l")
Encoder.longlong   = numbermarshaller(PrimitiveSizes.longlong  , "g")
Encoder.ushort     = numbermarshaller(PrimitiveSizes.ushort    , "S")
Encoder.ulong      = numbermarshaller(PrimitiveSizes.ulong     , "L")
Encoder.ulonglong  = numbermarshaller(PrimitiveSizes.ulonglong , "G")
Encoder.float      = numbermarshaller(PrimitiveSizes.float     , "f")
Encoder.double     = numbermarshaller(PrimitiveSizes.double    , "d")
Encoder.longdouble = numbermarshaller(PrimitiveSizes.longdouble, "D")
	
function Encoder:boolean(value)                                                 --[[VERBOSE]] verbose_marshal(true, self, idl.boolean)
	if value
		then self:octet(1)
		else self:octet(0)
	end                                                                           --[[VERBOSE]] verbose_marshal(false)
end

function Encoder:char(value)
	assert.type(value, "string", "character", "MARSHAL")
	if #value ~= 1 then
		assert.illegal(value, "character", "MARSHAL")
	end
	self:rawput('"', value, 1)                                                    --[[VERBOSE]] verbose_marshal(self, idl.char, value)
end

function Encoder:octet(value)
	assert.type(value, "number", "octet value", "MARSHAL")
	self:rawput("B", value, 1)                                                    --[[VERBOSE]] verbose_marshal(self, idl.octet, value)
end

local DefaultMapping = {
	number  = idl.double,
	string  = idl.string,
	boolean = idl.boolean,
	["nil"] = idl.null,
}
function Encoder:any(value)                                                     --[[VERBOSE]] verbose_marshal(true, self, idl.any)
	local luatype = type(value)
	local idltype = DefaultMapping[luatype]
	if not idltype then
		local metatable = getmetatable(value)
		if metatable then
			if idl.istype(metatable) then
				idltype = metatable
			elseif idl.istype(metatable.__type) then
				idltype = metatable.__type
			end
		end
		if luatype == "table" then
			if not idltype then
				idltype = value._anytype
				if not idl.istype(idltype) then
					idltype = nil
				end
			end
			if idltype then
				if (value._anyval ~= nil or NilEnabledTypes[idltype._type]) then
					value = value._anyval
				end
			end
		end
	end
	if not idltype then
		assert.illegal(value, "any, unable to map to an idl type", "MARSHAL")
	end                                                                           --[[VERBOSE]] verbose_marshal "[type of any]"
	self:TypeCode(idltype)                                                        --[[VERBOSE]] verbose_marshal "[value of any]"
	self:put(value, idltype)                                                      --[[VERBOSE]] verbose_marshal(false)
end

local NullReference = { type_id = "", profiles = { n=0 } }
function Encoder:Object(value, idltype)                                         --[[VERBOSE]] verbose_marshal(true, self, idltype, value)
	local reference
	if value == nil then
		reference = NullReference
	else
		local metatable = getmetatable(value)
		if metatable == giop.IOR
		or metatable and metatable.__type == giop.IOR
		then
			reference = value
		else
			assert.type(value, "table", "object reference", "MARSHAL")
			reference = value.__reference
			if not reference or reference == value then
				local servants = self.context.servants
				if servants then                                                        --[[VERBOSE]] verbose_marshal(true, "implicit servant creation")
					local objtype = servants:resolvetype(value) or idltype
					if not objtype:is_a(idltype.repID) then
						assert.illegal(value,
							idltype.repID..", got a "..objtype.repID, "BAD_PARAM")
					end
					value = assert.results(servants:register(value, nil, objtype))        --[[VERBOSE]] verbose_marshal(false)
					reference = value.__reference
				else
					assert.illegal(value, "Object, unable to create from value", "MARHSALL")
				end
			end
		end
	end
	self:struct(reference, giop.IOR)                                              --[[VERBOSE]] verbose_marshal(false)
end

function Encoder:struct(value, idltype)                                         --[[VERBOSE]] verbose_marshal(true, self, idltype)
	for _, field in ipairs(idltype.fields) do
		local val = value[field.name]                                               --[[VERBOSE]] verbose_marshal("[field ",field.name,"]")
		if val == nil and not NilEnabledTypes[field.type._type] then
			assert.illegal(value,
			              "struct value (no value for field "..field.name..")",
			              "MARSHAL")
		end
		self:put(val, field.type)
	end                                                                           --[[VERBOSE]] verbose_marshal(false)
end

function Encoder:union(value, idltype)                                          --[[VERBOSE]] verbose_marshal(true, self, idltype)
	assert.type(value, "table", "union value", "MARSHAL")
	local switch = value._switch

	-- Marshal discriminator
	if switch == nil then
		switch = idltype.selector[value._field]
		if switch == nil then
			for _, option in ipairs(idltype.options) do
				if value[option.name] ~= nil then
					switch = option.label
					break
				end
			end
			if switch == nil then
				switch = idltype.options[idltype.default+1]
				if switch == nil then
					assert.illegal(value, "union value (no discriminator)", "MARSHAL")
				end
			end
		end
	end                                                                           --[[VERBOSE]] verbose_marshal "[union switch]"
	self:put(switch, idltype.switch)
	
	local selection = idltype.selection[switch]
	if selection then
		-- Marshal union value
		local unionvalue = value._value
		if unionvalue == nil then
			unionvalue = value[selection.name]
			if unionvalue == nil then
				assert.illegal(value, "union value (none contents)", "MARSHAL")
			end
		end                                                                         --[[VERBOSE]] verbose_marshal("[field ",selection.name,"]")
		self:put(unionvalue, selection.type)
	end                                                                           --[[VERBOSE]] verbose_marshal(false)
end

function Encoder:enum(value, idltype)                                           --[[VERBOSE]] verbose_marshal(true, self, idltype, value)
	value = idltype.labelvalue[value] or tonumber(value)
	if not value then assert.illegal(value, "enum value", "MARSHAL") end
	self:ulong(value)                                                             --[[VERBOSE]] verbose_marshal(false)
end

function Encoder:string(value)                                                  --[[VERBOSE]] verbose_marshal(true, self, idl.string, value)
	assert.type(value, "string", "string value", "MARSHAL")
	local length = #value
	self:ulong(length + 1)
	self:rawput('"', value, length)
	self:rawput('"', '\0', 1)                                                     --[[VERBOSE]] verbose_marshal(false)
end

function Encoder:sequence(value, idltype)                                       --[[VERBOSE]] verbose_marshal(true, self, idltype, value)
	local elementtype = idltype.elementtype
	if type(value) == "string" then
		local length = #value
		self:ulong(length)
		while elementtype._type == "typedef" do
			elementtype = elementtype.original_type
		end
		if elementtype == idl.octet or elementtype == idl.char then
			self:rawput('"', value, length)
		else
			assert.illegal(value, "sequence value (table expected, got string)",
			                      "MARSHAL")
		end
	else
		assert.type(value, "table", "sequence value", "MARSHAL")
		local length = value.n or #value
		self:ulong(length)
		for i = 1, length do                                                        --[[VERBOSE]] verbose_marshal("[element ",i,"]")
			self:put(value[i], elementtype) 
		end
	end                                                                           --[[VERBOSE]] verbose_marshal(false)
end

function Encoder:array(value, idltype)                                          --[[VERBOSE]] verbose_marshal(true, self, idltype, value)
	local elementtype = idltype.elementtype
	if type(value) == "string" then
		while elementtype._type == "typedef" do
			elementtype = elementtype.original_type
		end
		if elementtype == idl.octet or elementtype == idl.char then
			local length = #value
			if length ~= idltype.length then
				assert.illegal(value, "array value (wrong length)", "MARSHAL")
			end
			self:rawput('"', value, length)
		else
			assert.illegal(value, "array value (table expected, got string)",
			                      "MARSHAL")
		end
	else
		assert.type(value, "table", "array value", "MARSHAL")
		for i = 1, idltype.length do                                                --[[VERBOSE]] verbose_marshal("[element ",i,"]")
			self:put(value[i], elementtype)
		end
	end                                                                           --[[VERBOSE]] verbose_marshal(false)
end

function Encoder:typedef(value, idltype)                                        --[[VERBOSE]] verbose_marshal(true, self, idltype, value)
	self:put(value, idltype.original_type)                                        --[[VERBOSE]] verbose_marshal(false)
end

function Encoder:except(value, idltype)                                         --[[VERBOSE]] verbose_marshal(true, self, idltype, value)
	assert.type(value, "table", "except value", "MARSHAL")
	for _, member in ipairs(idltype.members) do                                   --[[VERBOSE]] verbose_marshal("[member ", member.name, "]")
		local val = value[member.name]
		if val == nil and not NilEnabledTypes[member.type._type] then
			assert.illegal(value,
			              "except value (no value for member "..member.name..")",
			              "MARSHAL")
		end
		self:put(val, member.type)
	end                                                                           --[[VERBOSE]] verbose_marshal(false)
end

Encoder.interface = Encoder.Object

-- Abstract Interfaces ---------------------------------------------------------

local function index(indexable, field)
	return indexable[field]
end
local function pindex(indexable, field)
	local ok, value = pcall(index, indexable, field)
	if ok then return value end
end

function Encoder:abstract_interface(value, idltype)                             --[[VERBOSE]] verbose_marshal(true, self, idltype, value)
	-- get type of the value
	local actualtype = getmetatable(value)
	if not idl.istype(actualtype) then
		actualtype = pindex(actualtype, "__type")
		          or pindex(value, "__type")
	end
	local isvalue = (value == nil)
	             or (actualtype and actualtype._type == "valuetype")
	self:boolean(not isvalue)
	if isvalue then                                                               --[[VERBOSE]] verbose_marshal("value encoded as copied value")
		self:valuetype(value, idl.ValueBase)
	else                                                                          --[[VERBOSE]] verbose_marshal("value encoded as object reference")
		self:interface(value, idltype)
	end                                                                           --[[VERBOSE]] verbose_marshal(false)
end

-- ValueTypes ------------------------------------------------------------------

local MinValueTag = 0x7fffff00
local MaxValueTag = 0x7fffffff
local HasCodeBase = 0x00000001
local SingleRepID = 0x00000002
local ListOfRepID = 0x00000006
local ChunkedFlag = 0x00000008

local function reserve(self, size, noupdate)
	local sizeindex = self.ChunkSizeIndex
	if sizeindex then
		local newsize = size + (self[sizeindex] or MinValueTag)
		if newsize >= MinValueTag then -- update current chunk size
			if size >= MinValueTag then
				assert.illegal(data, "value too large", "MARSHAL")
			end                                                                       --[[VERBOSE]] verbose_marshal("[new encoding chunk]")
			self.ChunkSizeIndex = nil -- disable chunk encoding
			self:long(0) --[[start a new chunk (size is initially 0)]]
			sizeindex = self.index-1
			newsize = size
			self.ChunkSizeIndex = sizeindex                                           --[[VERBOSE]] SIZEINDEXPOS = self.cursor-PrimitiveSizes.long
		end
		if not noupdate then
			self[sizeindex] = newsize                                                 --[[VERBOSE]] CURSOR[SIZEINDEXPOS] = true
		end
	end
end

local function reservedalign(self, size)
	reserve(self, 0)
	return Encoder.align(self, size)
end

local function reservedrawput(self, format, data, size)
	reserve(self, size)
	return Encoder.rawput(self, format, data, size)
end

local ulongsize = PrimitiveSizes.ulong
local function reservedstring(self, value)
	reserve(self, alignment(self, ulongsize) -- alignment for the stating ulong
	            + ulongsize                  -- size of ulong with the string size
	            + #value                     -- number of bytes in the string
	            + 1,                         -- terminating '\0' of the string
	        "no update")
	return Encoder.string(self, value)
end

local function reservedsequence(self, value, idltype)
	local itemsize = PrimitiveSizes[idltype.elementtype._type]
	if itemsize then
		local count = (type(value) == "string") and #value or (value.n or #value)
		reserve(self, alignment(self, ulongsize) -- alignment for the ulong
		            + ulongsize                  -- size of ulong with item count
		            + count * itemsize,          -- size of the contents
		       "no update")
	end
	return Encoder.sequence(self, value, idltype)
end

local function reservedarray(self, value, idltype)
	local itemsize = PrimitiveSizes[idltype.elementtype._type]
	if itemsize then
		local count = (type(value) == "string") and #value or (value.n or #value)
		reserve(self, count * itemsize, "no update") -- size of the contents
	end
	return Encoder.array(self, value, idltype)
end

Encoder.ValueTypeNesting = 0

local abstract = idl.ValueKind.abstract
local truncatable = idl.ValueKind.truncatable
local function encodevaluetype(self, value, idltype)
	-- get type of the value
	local actualtype = getmetatable(value)
	if not idl.istype(actualtype) then
		actualtype = pindex(actualtype, "__type")
		          or pindex(value, "__type")
		          or (idltype.kind ~= abstract and idltype or nil)
	end
	assert.type(actualtype, "idl valuetype", "value type", "MARSHAL")
	-- collect typing information and check the type of the value
	local types = {}
	local type = actualtype
	local argidx -- index of the formal pararameter type
	local lstidx -- index of the last truncatable type
	for i = 1, math.huge do
		types[i] = type
		if type == idltype then argidx = i end
		if type.kind ~= truncatable then lstidx = i end
		type = type.base_value
		if type == idl.null then break end
	end
	local truncatable = (lstidx > 1)
	if argidx == nil then
		if idltype ~= idl.ValueBase then
			local found
			-- check whether it inherits from an abstract value
			if idltype.is_abstract then
				for _, type in ipairs(types) do
					if type:is_a(idltype.repID) then
						found = true
						break
					end
				end
			end
			if not found then
				assert.illegal(value, "value of type "..idltype.repID, "MARSHAL")
			end
		end
	elseif argidx < lstidx then
		lstidx = argidx -- can terminate the repID list at a well known type (param)
	end
	-- encode tag and typing information
	local nesting = self.ValueTypeNesting
	self.ChunkSizeIndex = nil -- end current chunk, if any
	local chunked = nesting > 0 or truncatable
	local tag = MinValueTag + (chunked and ChunkedFlag or 0)
	if actualtype == idltype and nesting == 0 then                                --[[VERBOSE]] verbose_marshal("[value tag: no truncatable bases]")
		self:ulong(tag)
	elseif chunked then --[[nesting > 0 or truncatable]]                          --[[VERBOSE]] verbose_marshal("[value tag: lists of ",lstidx," truncatable bases]")
		self:ulong(tag+ListOfRepID)
		self:long(lstidx)
		for i = 1, lstidx do                                                        --[[VERBOSE]] verbose_marshal("[repID of truncatable base ",i,"]")
			self:indirection(self.string, types[i].repID)
		end
	else -- non-truncatable
		self:ulong(tag+SingleRepID)                                                 --[[VERBOSE]] verbose_marshal("[value tag: single truncatable base]")
		self:indirection(self.string, types[1].repID)
	end
	-- check if chunked encoding is necessary
	if chunked then
		self.ValueTypeNesting = nesting+1  -- increase value nesting level
		if nesting == 0 then               -- enable chunked encoding if not nested
			self.history[reservedstring] = self.history[self.string]
			self.align = reservedalign
			self.rawput = reservedrawput
			self.string = reservedstring
			self.sequence = reservedsequence
			self.array = reservedarray
		end
		self.ChunkSizeIndex = "fake"       -- get prepared to start a new chunk
	end
	-- encode value state
	local membertype, membervalue
	for i = #types, 1, -1 do                                                      --[[VERBOSE]] verbose_marshal("[base value ",types[i].name,"]")
		local members = types[i].members
		local count = #members
		for j = 1, count do
			local member = members[j]                                                 --[[VERBOSE]] verbose_marshal("[field ",member.name,"]")
			membertype = member.type         -- used in optimization below
			membervalue = value[member.name]
			self:put(membervalue, membertype)
		end
	end
	-- finalize encoding of value
	if chunked then
		-- encode chunk end tag
		local endtag = -(nesting+1)
		if membertype
		and membertype._type == "valuetype"
		and membervalue ~= nil
		and self.ChunkSizeIndex == nil then
			self[self.index-1] = endtag      --[[last member was a ValueType]]        --[[VERBOSE]] verbose_marshal("[end tag of nested value updated to ",endtag,"] (optimized encoding)")
		else                                                                        --[[VERBOSE]] verbose_marshal("[end tag of encoded value]")
			self.ChunkSizeIndex = nil        -- terminate current chunk
			self:long(endtag)
		end
		self.ValueTypeNesting = nesting    -- restore value nesting level
		if nesting == 0 then               -- disable chunked encoding if not nested
			self.align = nil
			self.rawput = nil
			self.string = nil
			self.sequence = nil
			self.array = nil
			self.ChunkSizeIndex = nil
		else
			self.ChunkSizeIndex = "fake"     -- get prepared to start a new chunk
		end
	end
end

function Encoder:valuetype(value, idltype)                                          --[[VERBOSE]] verbose_marshal(true, self, idltype, value)
	if value == nil then
		self:ulong(0) -- null tag
	else
		assert.type(value, "table", "value", "MARSHAL")
		self:indirection(encodevaluetype, value, idltype)
	end                                                                           --[[VERBOSE]] verbose_marshal(false)
end

-- ValueBox --------------------------------------------------------------------

local function encodevaluebox(self, value, idltype)                            --[[VERBOSE]] verbose_marshal("[value tag: boxed]")
	local nesting = self.ValueTypeNesting
	-- encode tag
	self.ChunkSizeIndex = nil -- end current chunk, if any
	self:ulong(MinValueTag + (nesting==0 and 0 or ChunkedFlag))
	-- check if chunked encoding is necessary
	if nesting > 0 then
		self.ValueTypeNesting = nesting+1 -- increase value nesting level
		self.ChunkSizeIndex = "fake"      -- get prepared to start a new chunk
	end
	-- encode value
	self:put(value, idltype.original_type)
	-- finalize encoding of value
	if nesting > 0 then                                                           --[[VERBOSE]] verbose_marshal("[end tag of encoded value]")
		self.ChunkSizeIndex = nil         -- terminate current chunk
		self:long(-(nesting+1))           -- encode chunk end tag
		self.ValueTypeNesting = nesting-1 -- decrease value nesting level
		self.ChunkSizeIndex = "fake"      -- get prepared to start a new chunk
	end
end

function Encoder:valuebox(value, idltype)                                      --[[VERBOSE]] verbose_marshal(true, self, idltype, value)
	if value == nil then
		self:ulong(0) -- null tag
	else
		self:indirection(encodevaluebox, value, idltype)
	end                                                                           --[[VERBOSE]] verbose_marshal(false)
end

-- TypeCodes -------------------------------------------------------------------

local function encodetypeinfo(self, value, kind, tcinfo)
	self:ulong(kind)
	local tcparams = value.tcparams
	if tcparams == nil then                                                       --[[VERBOSE]] verbose_marshal "[parameters values]"
		-- create encoder for encapsulated stream
		local cursor = self.previousend+self.cursor
		local history
		if self.encodingTypeCode then
			history = self.history
		else
			history = newhistory()
			history[encodetypeinfo][value] = self.history[encodetypeinfo][value]
		end
		local encoder = Encoder{
			context = self.context,
			history = history,
			previousend = cursor-1 + 4, -- adds the size of the OctetSeq count
			encodingTypeCode = true,
		}
		encoder:boolean(NativeEndianess) -- encapsulated stream includes endianess
		-- encode parameters using the encapsulated encoder
		encoder:struct(value, tcinfo.parameters)
		if tcinfo.mutable then                                                      --[[VERBOSE]] verbose_marshal "[mutable parameters values]"
			for _, param in ipairs(tcinfo.mutable:setup(value)) do
				encoder:put(value[param.name], param.type)
			end
		end                                                                         --[[VERBOSE]] verbose_marshal(true, "[parameters encapsulation]")
		-- get encapsulated stream and save for future reuse
		tcparams = encoder:getdata()
		if not self.encodingTypeCode then
			value.tcparams = tcparams
		end                                                                         --[[VERBOSE]] verbose_marshal(false)
	end
	self:sequence(tcparams, idl.OctetSeq)
end

local TypeCodes = { interface = 14 }
for tcode, info in pairs(TypeCodeInfo) do TypeCodes[info.name] = tcode end

function Encoder:TypeCode(value)                                                --[[VERBOSE]] verbose_marshal(true, self, idl.TypeCode, value)
	assert.type(value, "idl type", "TypeCode value", "MARSHAL")
	local kind   = TypeCodes[value._type]
	local tcinfo = TypeCodeInfo[kind]

	if not kind then assert.illegal(value, "idl type", "MARSHAL") end
	
	if tcinfo.type == "empty" then
		self:ulong(kind)
	elseif tcinfo.type == "simple" then
		self:ulong(kind)
		for _, param in ipairs(tcinfo.parameters) do                                --[[VERBOSE]] verbose_marshal("[parameter ",param.name,"]")
			self:put(value[param.name], param.type)
		end
	else
		self:indirection(encodetypeinfo, value, kind, tcinfo)
	end                                                                           --[[VERBOSE]] verbose_marshal(false)
end

--------------------------------------------------------------------------------
--##  ##  ##  ##  ##   ##   ####   #####    ####  ##  ##   ####   ##     ##   --
--##  ##  ### ##  ### ###  ##  ##  ##  ##  ##     ##  ##  ##  ##  ##     ##   --
--##  ##  ######  #######  ######  #####    ###   ######  ######  ##     ##   --
--##  ##  ## ###  ## # ##  ##  ##  ##  ##     ##  ##  ##  ##  ##  ##     ##   --
-- ####   ##  ##  ##   ##  ##  ##  ##  ##  ####   ##  ##  ##  ##  #####  #####--
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
-- Unmarshalling buffer class --------------------------------------------------

Decoder = oo.class{
	previousend = 0,
	cursor = 1,
	align = Encoder.align,
	unpack = bit.unpack, -- use current platform native endianess
}

function Decoder:__init(object)
	self = oo.rawnew(self, object)
	if self.history == nil then self.history = {} end
	return self
end

function Decoder:order(value)
	if value ~= NativeEndianess then
		self.unpack = bit.invunpack
	end
end

function Decoder:jump(shift)
	local cursor = self.cursor
	if shift > 0 then                                                             --[[VERBOSE]] CURSOR[self.cursor] = true; if CODEC == nil then CODEC = self end
		self.cursor = cursor + shift                                                --[[VERBOSE]] CURSOR[self.cursor] = false
		if self.cursor - 1 > #self.data then
			assert.illegal(self.data, "data stream, insufficient data", "MARSHAL")
		end
	end
	return cursor
end

function Decoder:indirection(unmarshal, ...)
	local value
	local tag = self:ulong()
	if tag == IndirectionTag then                                                 --[[VERBOSE]] verbose_unmarshal("indirection tag found")
		local pos = self.previousend+self.cursor
		local offset = self:long()
		value = self.history[pos+offset]                                            --[[VERBOSE]] verbose_unmarshal(value == nil and "no " or "","previous value found at position ",pos+offset," (current: ",pos,")")
		if value == nil then
			assert.illegal(offset, "indirection offset", "MARSHAL")
		end
	else
		local pos = self.previousend+self.cursor - PrimitiveSizes.ulong             --[[VERBOSE]] verbose_unmarshal("calculating position of value for indirections, got ",pos)
		value = unmarshal(self, pos, tag, ...)
	end
	return value
end

function Decoder:get(idltype)
	local unmarshal = self[idltype._type]
	if not unmarshal then
		assert.illegal(idltype._type, "supported type", "MARSHAL")
	end
	return unmarshal(self, idltype)
end

function Decoder:append(data)
	self.data = self.data..data
end

function Decoder:getdata()
	return self.data
end

--------------------------------------------------------------------------------
-- Unmarshalling functions -----------------------------------------------------

local function numberunmarshaller(size, format)
	return function(self)
		self:align(size)
		local cursor = self:jump(size)                                              --[[VERBOSE]] verbose_unmarshal(self, format, self.unpack(format, self.data, nil, nil, cursor))
		return self.unpack(format, self.data, nil, nil, cursor)
	end
end

Decoder.null       = function() end
Decoder.void       = Decoder.null
Decoder.short      = numberunmarshaller(PrimitiveSizes.short     , "s")
Decoder.long       = numberunmarshaller(PrimitiveSizes.long      , "l")
Decoder.longlong   = numberunmarshaller(PrimitiveSizes.longlong  , "g")
Decoder.ushort     = numberunmarshaller(PrimitiveSizes.ushort    , "S")
Decoder.ulong      = numberunmarshaller(PrimitiveSizes.ulong     , "L")
Decoder.ulonglong  = numberunmarshaller(PrimitiveSizes.ulonglong , "G")
Decoder.float      = numberunmarshaller(PrimitiveSizes.float     , "f")
Decoder.double     = numberunmarshaller(PrimitiveSizes.double    , "d")
Decoder.longdouble = numberunmarshaller(PrimitiveSizes.longdouble, "D")

function Decoder:boolean()                                                      --[[VERBOSE]] verbose_unmarshal(true, self, idl.boolean)
	return (self:octet() ~= 0)                                                    --[[VERBOSE]],verbose_unmarshal(false)
end

function Decoder:char()
	local cursor = self:jump(1) --[[check if there is enougth bytes]]             --[[VERBOSE]] verbose_unmarshal(self, idl.char, self.data:sub(cursor, cursor))
	return self.data:sub(cursor, cursor)
end

function Decoder:octet()
	local cursor = self:jump(1) --[[check if there is enougth bytes]]             --[[VERBOSE]] verbose_unmarshal(self, idl.octet, self.unpack("B", self.data, nil, nil, cursor))
	return self.unpack("B", self.data, nil, nil, cursor)
end

function Decoder:any()                                                          --[[VERBOSE]] verbose_unmarshal(true, self, idl.any) verbose:unmarshal "[type of any]"
	local idltype = self:TypeCode()                                               --[[VERBOSE]] verbose_unmarshal "[value of any]"
	local value = self:get(idltype)
	if type(value) == "table" then
		value._anyval = value
		value._anytype = idltype
	else
		value = setmetatable({
			_anyval = value,
			_anytype = idltype,
		}, idltype)
	end                                                                           --[[VERBOSE]] verbose_unmarshal(false)
	return value
end

function Decoder:Object(idltype)                                                --[[VERBOSE]] verbose_unmarshal(true, self, idltype)
	local ior = self:struct(giop.IOR)
	if ior.type_id == "" then                                                     --[[VERBOSE]] verbose_unmarshal "got a null reference"
		ior = nil
	else
		local proxies = self.context.proxies
		if proxies then                                                             --[[VERBOSE]] verbose_unmarshal(true, "retrieve proxy for referenced object")
			if idltype._type == "Object" then idltype = idltype.repID end
			ior = assert.results(proxies:resolve(ior, idltype))                       --[[VERBOSE]] verbose_unmarshal(false)
		end
	end                                                                           --[[VERBOSE]] verbose_unmarshal(false)
	return ior
end

function Decoder:struct(idltype)                                                --[[VERBOSE]] verbose_unmarshal(true, self, idltype)
	local value = {}
	for _, field in ipairs(idltype.fields) do                                     --[[VERBOSE]] verbose_unmarshal("[field ",field.name,"]")
		value[field.name] = self:get(field.type)
	end                                                                           --[[VERBOSE]] verbose_unmarshal(false)
	return setmetatable(value, idltype)
end

function Decoder:union(idltype)                                                 --[[VERBOSE]] verbose_unmarshal(true, self, idltype) verbose:unmarshal "[union switch]"
	local switch = self:get(idltype.switch)
	local value = { _switch = switch }
	local option = idltype.selection[switch] or
	               idltype.options[idltype.default+1]
	if option then                                                                --[[VERBOSE]] verbose_unmarshal("[field ",option.name,"]")
		value._field = option.name
		value._value = self:get(option.type)
	end                                                                           --[[VERBOSE]] verbose_unmarshal(false)
	return setmetatable(value, idltype)
end

function Decoder:enum(idltype)                                                  --[[VERBOSE]] verbose_unmarshal(true, self, idltype)
	local value = self:ulong() + 1
	if value > #idltype.enumvalues then
		assert.illegal(value, "enumeration value", "MARSHAL")
	end                                                                           --[[VERBOSE]] verbose_unmarshal(false, "got ",idltype.enumvalues[value])
	return idltype.enumvalues[value]
end

function Decoder:indirectstring(pos, length)
	local cursor = self:jump(length) -- check if there is enougth bytes
	local value = self.data:sub(cursor, cursor + length - 2)
	if pos then self.history[pos] = value end                                     --[[VERBOSE]] verbose_unmarshal("got ",verbose.viewer:tostring(value))
	return value
end

function Decoder:string()                                                       --[[VERBOSE]] verbose_unmarshal(true, self, idl.string)
	return self:indirectstring(nil, self:ulong())                                 --[[VERBOSE]],verbose_unmarshal(false)
end

function Decoder:sequence(idltype)                                              --[[VERBOSE]] verbose_unmarshal(true, self, idltype)
	local length      = self:ulong()
	local elementtype = idltype.elementtype
	local value
	while elementtype._type == "typecode" do elementtype = elementtype.type end
	if elementtype == idl.octet or elementtype == idl.char then
		local cursor = self:jump(length) -- check if there is enougth bytes
		value = self.data:sub(cursor, cursor + length - 1)                          --[[VERBOSE]] verbose_unmarshal("got ", verbose.viewer:tostring(value))
	else
		value = setmetatable({ n = length }, idltype)
		for i = 1, length do                                                        --[[VERBOSE]] verbose_unmarshal("[element ",i,"]")
			value[i] = self:get(elementtype)
		end
	end                                                                           --[[VERBOSE]] verbose_unmarshal(false)
	return value
end

function Decoder:array(idltype)                                                 --[[VERBOSE]] verbose_unmarshal(true, self, idltype)
	local length      = idltype.length
	local elementtype = idltype.elementtype
	local value
	while elementtype._type == "typecode" do elementtype = elementtype.type end
	if elementtype == idl.octet or elementtype == idl.char then
		local cursor = self:jump(length) -- check if there is enougth bytes
		value = self.data:sub(cursor, cursor + length - 1)                          --[[VERBOSE]] verbose_unmarshal("got ",verbose.viewer:tostring(value))
	else
		value = setmetatable({}, idltype)
		for i = 1, length do                                                        --[[VERBOSE]] verbose_unmarshal("[element ",i,"]")
			value[i] = self:get(elementtype)
		end
	end                                                                           --[[VERBOSE]] verbose_unmarshal(false)
	return value
end

function Decoder:typedef(idltype)                                               --[[VERBOSE]] verbose_unmarshal(true, self, idltype)
	return self:get(idltype.original_type)                                        --[[VERBOSE]],verbose_unmarshal(false)
end

function Decoder:except(idltype)                                                --[[VERBOSE]] verbose_unmarshal(true, self, idltype)
	local value = {}
	for _, member in ipairs(idltype.members) do                                   --[[VERBOSE]] verbose_unmarshal("[member ",member.name,"]")
		value[member.name] = self:get(member.type)
	end                                                                           --[[VERBOSE]] verbose_unmarshal(false)
	return setmetatable(value, idltype)
end

Decoder.interface = Decoder.Object

function Decoder:abstract_interface(idltype)                                    --[[VERBOSE]] verbose_unmarshal(true, self, idltype)
	local value
	if self:boolean() then                                                        --[[VERBOSE]] verbose_unmarshal("value is a copied value")
		value = self:interface(idltype)
	else                                                                          --[[VERBOSE]] verbose_unmarshal("value is an object reference")
		value = self:valuetype(idl.ValueBase)
	end                                                                           --[[VERBOSE]] verbose_unmarshal(false)
	return value
end

-- ValueTypes ------------------------------------------------------------------

Decoder.ValueTypeNesting = 0

local decodevaluetype

local function reservedjump(self, shift)
	self.jump = nil -- disable chunk decoding
	local chunkend = self.ChunkEnd
	if chunkend == nil then
		local cursor = self.cursor
		local value = self:long()
		if value >= MinValueTag then                                                --[[VERBOSE]] verbose_unmarshal("found nested value in chunked encoding")
			self.cursor = cursor+shift -- rollback the cursor
			return cursor -- return with chunk decoding disabled 
		elseif value > 0 then
			chunkend = self.cursor + value -- calculate new chunk end
			self.ChunkEnd = chunkend                                                  --[[VERBOSE]] verbose_unmarshal("value encoding chunk started (end at ",chunkend,")")
		else -- end tag
			assert.illegal(self.data,
				"data stream, chunked value encoding ended prematurely", "MARSHAL")
		end
	end
	local result = self:jump(shift)
	if self.cursor == chunkend then                                               --[[VERBOSE]] verbose_unmarshal("value encoding chunk finished")
		self.ChunkEnd = nil
	elseif chunkend and self.cursor > chunkend then
		assert.illegal(self.data,
			"data stream, value chunk ended prematurely", "MARSHAL")
	end
	self.jump = reservedjump -- re-enable chunk decoding
	return result
end

local function skipchunks(self, nesting)
	self.jump = nil
	local chunkend = self.ChunkEnd
	if chunkend then                                                              --[[VERBOSE]] verbose_unmarshal("skipping the remains of current chunk")
		self:jump(chunkend - self.cursor)
		self.ChunkEnd = nil
	end
	repeat
		local value = self:long()
		if value >= MinValueTag then                                                --[[VERBOSE]] verbose_unmarshal(true, "skipping nested value")
			local pos = self.previousend+self.cursor - PrimitiveSizes.ulong           --[[VERBOSE]] verbose_unmarshal("calculating position of value for indirections, got ",pos)
			value = decodevaluetype(self, pos, value)                                 --[[VERBOSE]] verbose_unmarshal(false)
			self.jump = nil
		elseif value > 0 then                                                       --[[VERBOSE]] verbose_unmarshal("skipping an entire chunk")
			self:jump(value)
		else -- end tag
			self.ValueTypeNesting = -(value+1)                                        --[[VERBOSE]] verbose_unmarshal("found the end tag of a nested value, restoring to nesting level ",self.ValueTypeNesting)
		end
	until self.ValueTypeNesting <= nesting
	if self.ValueTypeNesting > 0 then self.jump = reservedjump end
end

local truncatable = idl.ValueKind.truncatable
local function decodevaluestate(self, value, idltype, repidlist, chunked)
	-- check if chunked decoding is necessary
	local nesting
	if chunked then
		-- increase value nesting level
		nesting = self.ValueTypeNesting
		self.ValueTypeNesting = nesting+1
		-- enable chunked decoding
		self:align(PrimitiveSizes.long)
		self.jump = reservedjump
	end
	-- find value's type description
	local type
	if repidlist == 0 then
		type = idltype
	else
		local types = self.context.types
		if types then
			for i = 1, #repidlist do
				local repID = repidlist[i]
				type = types:resolve(repID)
				if type ~= nil then break end                                           --[[VERBOSE]] verbose_unmarshal("skipping unknown truncatable base ",repID)
			end
		end
		if type == nil then
			assert.illegal(value,
				"value, all truncatable bases are unknown", "MARSHAL")
		end
		assert.type(type, "idl valuetype", "type of received value", "MARSHAL")
	end                                                                           --[[VERBOSE]] verbose_unmarshal("decoding value as a ",type.name)
	setmetatable(value, type)
	-- collect all base types
	local types = {}
	for i = 1, math.huge do
		types[i] = type
		type = type.base_value
		if type == idl.null then break end
	end
	-- decode value state
	for i = #types, 1, -1 do                                                      --[[VERBOSE]] verbose_unmarshal("[base value ",types[i].name,"]")
		local members = types[i].members
		for j = 1, #members do
			local member = members[j]                                                 --[[VERBOSE]] verbose_unmarshal("[field ",member.name,"]")
			value[member.name] = self:get(member.type)
		end
	end
	-- finalize decoding of value
	if chunked then
		skipchunks(self, nesting) -- skip the remains of this value
	end
	-- construct the value using the factory
	local factory = self.context.factories
	if factory then
		factory = factory[types[1].repID]
		if factory then                                                             --[[VERBOSE]] verbose_unmarshal(true, "building value using factory of ",types[1].repID)
			factory(value)                                                            --[[VERBOSE]] verbose_unmarshal(false) else verbose_unmarshal("no factory found for ",types[1].repID)
		end
	end
end

function decodevaluetype(self, pos, tag, idltype)
	-- check for null tag
	if tag == 0 then
		return nil                                                                  --[[VERBOSE]],verbose_unmarshal("got a null")
	end
	-- check tag value
	if tag < MinValueTag or tag > MaxValueTag then
		assert.illegal(tag, "value tag", "MARSHAL")
	end
	-- decode flags contained in the tag
	local codebase = tag%2
	tag = tag-codebase
	local repidlist = tag%8
	tag = tag-repidlist
	local chunked = (tag%16 == ChunkedFlag)
	-- ignore CodeBaseURL string if present
	if codebase == HasCodeBase then                                               --[[VERBOSE]] verbose_unmarshal("[CodeBaseURL: ignored]")
		self:indirection(self.indirectstring)
	end
	-- decode typing information
	if repidlist == SingleRepID then                                              --[[VERBOSE]] verbose_unmarshal("[single truncatable base]")
		repidlist = { self:indirection(self.indirectstring) }
	elseif repidlist == ListOfRepID then                                          --[[VERBOSE]] verbose_unmarshal("[list of truncatable bases]")
		repidlist = {}
		for i = 1, self:long() do
			repidlist[i] = self:indirection(self.indirectstring)
		end
	elseif repidlist ~= 0 then
		assert.illegal(repidlist,
			"type information bit pattern in value tag (only 0, "
			..SingleRepID.." and "..ListOfRepID.." are valid)", "MARSHAL")
	end
	-- create value
	local value = {}
	self.history[pos] = value
	if idltype == nil then                                                        --[[VERBOSE]] verbose_unmarshal(true, "skipping chunks of a nested value inside a chunked value")
		-- skipping chunks of a nested value
		local cursor = self.cursor
		local nesting = self.ValueTypeNesting
		function value._complete(_, idltype)                                        --[[VERBOSE]] verbose_unmarshal(true, "resuming decoding of previously skipped nested value")
			value._complete = nil
			local cursor_back = self.cursor
			local nesting_back = self.ValueTypeNesting
			local chunkend_back = self.ChunkEnd
			local jump_back = rawget(self, "jump")
			self.cursor = cursor
			self.ValueTypeNesting = nesting
			self.ChunkEnd = nil
			self.jump = nil
			decodevaluestate(self, value, idltype, repidlist, chunked)
			self.cursor = cursor_back
			self.ValueTypeNesting = nesting_back                                      --[[VERBOSE]] verbose_unmarshal(false)
			self.ChunkEnd = chunkend_back
			self.jump = jump_back
		end
		self.ValueTypeNesting = nesting+1
		skipchunks(self, nesting)                                                   --[[VERBOSE]] verbose_unmarshal(false)
	else
		decodevaluestate(self, value, idltype, repidlist, chunked)
	end
	return value
end

function Decoder:valuetype(idltype)                                              --[[VERBOSE]] verbose_unmarshal(true, self, idltype)
	local value = self:indirection(decodevaluetype, idltype)
	if value and value._complete then value:_complete() end                       --[[VERBOSE]] verbose_unmarshal(false)
	return value
end

-- ValueBox --------------------------------------------------------------------

local function decodevaluebox(self, pos, tag, idltype)
	-- check for null tag
	if tag == 0 then
		return nil                                                                  --[[VERBOSE]],verbose_unmarshal("got a null")
	end
	-- check tag value
	local chunked = (tag == MinValueTag+ChunkedFlag)
	if not chunked and tag ~= MinValueTag then
		assert.illegal(tag, "value box tag", "MARSHAL")
	end
	-- check if chunked decoding is necessary
	local nesting
	if chunked then
		-- increase value nesting level
		nesting = self.ValueTypeNesting
		self.ValueTypeNesting = nesting+1
		-- enable chunked decoding
		self:align(PrimitiveSizes.long)
		self.jump = reservedjump
	end
	-- decode value state
	local value = self:get(idltype.original_type)
	self.history[pos] = value
	-- finalize decoding of value
	if chunked then
		skipchunks(self, nesting) -- skip the remains of this value
	end
	return value
end

function Decoder:valuebox(idltype)                                             --[[VERBOSE]] verbose_unmarshal(true, self, idltype)
	return self:indirection(decodevaluebox, idltype)                              --[[VERBOSE]],verbose_unmarshal(false)
end

--------------------------------------------------------------------------------

local function decodetypeinfo(self, pos, kind)
	local tcinfo = TypeCodeInfo[kind]
	if tcinfo == nil then assert.illegal(kind, "type code", "MARSHAL") end        --[[VERBOSE]] verbose_unmarshal("TypeCode defines a ",tcinfo.name)
	if tcinfo.unhandled then
		assert.illegal(tcinfo.name, "supported type code", "MARSHAL")
	end
	if tcinfo.type == "empty" then
		return tcinfo.idl
	elseif tcinfo.type == "simple" then
		-- NOTE: The string type is the only simple type being handled,
		--       therefore parameters are ignored.
		for _, param in ipairs(tcinfo.parameters) do                                --[[VERBOSE]] verbose_unmarshal("[parameter ",param.name,"]")
			self:get(param.type)
		end
		return tcinfo.idl
	elseif tcinfo.type == "complex" then                                          --[[VERBOSE]] verbose_unmarshal(true, "[parameters encapsulation]")
		local tcparams = self:sequence(idl.OctetSeq)
		local value = { _type = tcinfo.name }
		local history = self.history
		history[pos] = value
		if not self.encodingTypeCode then
			history = { [pos] = value } -- do not inherit history, as it is standalone
			value.tcparams = tcparams
		end
		-- create decoder for encapsulated stream
		local cursor = self.previousend+self.cursor
		local decoder = Decoder{
			data = tcparams,
			context = self.context,
			history = history,
			previousend = cursor-1 - #tcparams, -- rolls back before the OctetSeq read
			encodingTypeCode = true,
		}
		decoder:order(decoder:boolean()) -- encapsulated stream includes endianess
		-- encode parameters using the encapsulated encoder
		for _, field in ipairs(tcinfo.parameters.fields) do                         --[[VERBOSE]] verbose_unmarshal("[field ",field.name,"]")
			value[field.name] = decoder:get(field.type)
		end
		if tcinfo.mutable then                                                      --[[VERBOSE]] verbose_unmarshal "[mutable parameters values]"
			for _, param in ipairs(tcinfo.mutable:setup(value)) do
				value[param.name] = decoder:get(param.type)
			end
		end                                                                         --[[VERBOSE]] verbose_unmarshal(false)
		-- build local TypeCode value
		return idl[tcinfo.name](value)
	end
end

function Decoder:TypeCode()                                                     --[[VERBOSE]] verbose_unmarshal(true, self, idl.TypeCode)
	return self:indirection(decodetypeinfo)                                       --[[VERBOSE]],verbose_unmarshal(false)
end

--------------------------------------------------------------------------------
--------------------------------------------------------------------------------

-- NOTE: second parameter indicates an encasulated octet-stream, therefore
--       endianess must be read from stream.
function decoder(self, octets, getorder)
	local decoder = self.Decoder{
		data = octets,
		context = self,
	}
	if getorder then decoder:order(decoder:boolean()) end
	return decoder
end

-- NOTE: Presence of a parameter indicates an encapsulated octet-stream.
function encoder(self, putorder)
	local encoder = self.Encoder{ context = self }
	if putorder then encoder:boolean(NativeEndianess) end
	return encoder
end

--------------------------------------------------------------------------------
--------------------------------------------------------------------------------

--[[VERBOSE]] local numtype = {
--[[VERBOSE]] 	s = idl.short,
--[[VERBOSE]] 	l = idl.long,
--[[VERBOSE]] 	g = idl.longlong,
--[[VERBOSE]] 	S = idl.ushort,
--[[VERBOSE]] 	L = idl.ulong,
--[[VERBOSE]] 	G = idl.ulonglong,
--[[VERBOSE]] 	f = idl.float,
--[[VERBOSE]] 	d = idl.double,
--[[VERBOSE]] 	D = idl.longdouble,
--[[VERBOSE]] }
--[[VERBOSE]] verbose.codecop = {
--[[VERBOSE]] 	[Encoder] = "marshal",
--[[VERBOSE]] 	[Decoder] = "unmarshal",
--[[VERBOSE]] }
--[[VERBOSE]] local luatype = type
--[[VERBOSE]] function verbose.custom:marshal(codec, type, value)
-- [[VERBOSE]] 	if CODEC and self.flags.hexastream then
-- [[VERBOSE]] 		self.hexastream(self, CODEC, CURSOR)
-- [[VERBOSE]] 		CURSOR, CODEC = {}, nil
-- [[VERBOSE]] 	end
--[[VERBOSE]] 	local viewer = self.viewer
--[[VERBOSE]] 	local output = viewer.output
--[[VERBOSE]] 	local op = self.codecop[oo.classof(codec)]
--[[VERBOSE]] 	if op then
--[[VERBOSE]] 		type = numtype[type] or type
--[[VERBOSE]] 		output:write(op," of ",type._type)
--[[VERBOSE]] 		type = type.name or type.repID
--[[VERBOSE]] 		if type then
--[[VERBOSE]] 			output:write(" ",type)
--[[VERBOSE]] 		end
--[[VERBOSE]] 		if value ~= nil then
--[[VERBOSE]] 			if luatype(value) == "string" then
--[[VERBOSE]] 				value = value:gsub("[^%w%p%s]", "?")
--[[VERBOSE]] 			end
--[[VERBOSE]] 			output:write(" (got ")
--[[VERBOSE]] 			viewer:write(value)
--[[VERBOSE]] 			output:write(")")
--[[VERBOSE]] 		end
--[[VERBOSE]] 	else
--[[VERBOSE]] 		return true -- cancel custom message
--[[VERBOSE]] 	end
--[[VERBOSE]] end
--[[VERBOSE]] verbose.custom.unmarshal = verbose.custom.marshal
--[[VERBOSE]] 
--[[VERBOSE]] function verbose_marshal(...)
--[[VERBOSE]] 	verbose:marshal(...)
--[[VERBOSE]] 	if CODEC and verbose.flags.hexastream then
--[[VERBOSE]] 		if CURSOR[SIZEINDEXPOS] and CODEC.ChunkSizeIndex then
--[[VERBOSE]] 			verbose:marshal("[chunk size updated to ",CODEC[CODEC.ChunkSizeIndex],"]")
--[[VERBOSE]] 		end
--[[VERBOSE]] 		verbose:hexastream(CODEC, CURSOR, PREFIXSHIFT)
--[[VERBOSE]] 		CURSOR, CODEC = {}, nil
--[[VERBOSE]] 	end
--[[VERBOSE]] end
--[[VERBOSE]] function verbose_unmarshal(...)
--[[VERBOSE]] 	verbose:unmarshal(...)
--[[VERBOSE]] 	if CODEC and verbose.flags.hexastream then
--[[VERBOSE]] 		if CURSOR[SIZEINDEXPOS] and CODEC.ChunkSizeIndex then
--[[VERBOSE]] 			verbose:marshal("[chunk size updated to ",CODEC[CODEC.ChunkSizeIndex],"]")
--[[VERBOSE]] 		end
--[[VERBOSE]] 		verbose:hexastream(CODEC, CURSOR)
--[[VERBOSE]] 		CURSOR, CODEC = {}, nil
--[[VERBOSE]] 	end
--[[VERBOSE]] end
