#!/usr/bin/env lua
--------------------------------------------------------------------------------
-- @script  IDL Descriptor Pre-Loader
-- @version 1.0
-- @author  Renato Maia <maia@tecgraf.puc-rio.br>
--

local assert     = assert
local pairs      = pairs
local select     = select
local io         = require "io"
local os         = require "os"
local string     = require "string"
local luaidl     = require "luaidl"
local idl        = require "oil.corba.idl"
local Compiler   = require "oil.corba.idl.Compiler"
local Serializer = require "loop.serial.Serializer"

module("idl2lua", require "loop.compiler.Arguments")

output  = "idl.lua"
broker  = "require('oil').init()"
include = {}

_alias = { I = "include" }
for name in pairs(_M) do
	_alias[name:sub(1, 1)] = name
end

local start, errmsg = _M(...)
local finish = select("#", ...)
if not start or start ~= finish then
	if errmsg then io.stderr:write("ERROR: ", errmsg, "\n") end
	io.stderr:write([[
IDL Descriptor Pre-Parser 1.1  Copyright (C) 2006-2008 Tecgraf, PUC-Rio
Usage: ]].._NAME..[[.lua [options] <idlfile>
Options:
  
  -o, -output       Output file that should be generated. Its default is
                    ']],output,[['.
  
  -b, -broker       ORB instance the IDL must be loaded to. Its default
                    is ']],instance,[[' that denotes the instance returned
                    by the 'oil' package.
  
  -I, i, -include   Adds a directory to the list of paths where the IDL files
                    are searched.

]])
	os.exit(1)
end

--------------------------------------------------------------------------------

local file = assert(io.open(output, "w"))

local stream = Serializer()
function stream:write(...)
	return file:write(...)
end

stream[idl]              = "idl"
stream[idl.void]         = "idl.void"
stream[idl.short]        = "idl.short"
stream[idl.long]         = "idl.long"
stream[idl.longlong]     = "idl.longlong"
stream[idl.ushort]       = "idl.ushort"
stream[idl.ulong]        = "idl.ulong"
stream[idl.ulonglong]    = "idl.ulonglong"
stream[idl.float]        = "idl.float"
stream[idl.double]       = "idl.double"
stream[idl.longdouble]   = "idl.longdouble"
stream[idl.boolean]      = "idl.boolean"
stream[idl.char]         = "idl.char"
stream[idl.octet]        = "idl.octet"
stream[idl.any]          = "idl.any"
stream[idl.TypeCode]     = "idl.TypeCode"
stream[idl.string]       = "idl.string"
stream[idl.object]       = "idl.object"
stream[idl.basesof]      = "idl.basesof"
stream[idl.Contents]     = "idl.Contents"
stream[idl.ContainerKey] = "idl.ContainerKey"

local compiler = Compiler()
compiler.defaults.incpath = include

file:write(broker,[[.TypeRepository.types:register(
	setfenv(
		function()
			return ]])

stream:serialize(assert(luaidl.parsefile(select(start, ...),
                                         compiler.defaults)))
file:write([[ 
		end,
		{
			idl = require "oil.corba.idl",
			]],stream.namespace,[[ = require("loop.serial.Serializer")(),
		}
	)()
)
]])
file:close()
