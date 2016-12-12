--
-- Project:  LuaIDL
-- Author:   Ricardo Cosme <rcosme@tecgraf.puc-rio.br>
-- Filename: init.lua
-- 
local assert  = assert
local error   = error
local pcall   = pcall
local require = require
local type    = type
local unpack  = unpack

local io      = require "io"
local os      = require "os"
local string  = require "string"

module 'luaidl'

local preprocessor  = require 'luaidl.pre'
local parser        = require 'luaidl.sin'

VERSION = '1.0.5'

---
-- Auxiliar functions
--------------------------------------------------------------------------

local function parseAux(idl, options)
  local status, output = pcall(parser.parse, idl, options)
  if status then
    return unpack(output)
  else
    return nil, output
  end
end
--------------------------------------------------------------------------


---
-- API
--------------------------------------------------------------------------

--- Preprocesses an IDL code. 
-- 
-- @param idl String with IDL code.
-- @param options (optional)Table with preprocessor options, the available keys are:
-- 'incpath', a table with include paths;
-- 'filename', the IDL filename.
-- @return String with the given IDL preprocessed.
function pre(idl, options)
  return preprocessor.run(idl, options)
end

--- Preprocesses an IDL file.
-- 
-- @param filename The IDL filename.
-- @param options (optional)Table with preprocessor options, the available keys are:
-- 'incpath', a table with include paths.
-- @return String with the given IDL preprocessed.
-- @see pre
function prefile(filename, options)
  local _type = type(filename)
  if (_type ~= "string") then
    error(string.format("bad argument #1 to 'prefile' (filename expected, got %s)", _type), 2)
  end --if
  local fh, msg = io.open(filename)
  if not fh then
    error(msg, 2)
  end --if
  if not options then
    options = { }
  end
  options.filename = filename
  local str = pre(fh:read('*a'), options)
  fh:close()
  return str
end

--- Parses an IDL code.
-- 
-- @param idl String with IDL code.
-- @param options (optional)Table with parser and preprocessor options, the available keys are:
-- 'callbacks', a table of callback methods;
-- 'incpath', a table with include paths;
-- 'filename',the IDL filename.
-- @return A graph(lua table),
-- that represents an IDL definition in Lua, for each IDL definition found.
function parse(idl, options)
  idl = pre(idl, options)
  return parseAux(idl, options)
end

--- Parses an IDL file.
-- Calls the method 'prefile' with 
-- the given arguments, and so it parses the output of 'prefile'
-- calling the method 'parse'.
-- @param filename The IDL filename.
-- @param options (optional)Table with parser and preprocessor options, the available keys are:
-- 'callbacks', a table of callback methods;
-- 'incpath', a table with include paths.
-- @return A graph(lua table),
-- that represents an IDL definition in Lua, for each IDL definition found.
-- @see prefile 
-- @see parse
function parsefile(filename, options)
  local _type = type(filename)
  if (_type ~= "string") then
    error(string.format("bad argument #1 to 'parsefile' (filename expected, got %s)", _type), 2)
  end
  local stridl = prefile(filename, options)
  return parseAux(stridl, options)
end
--------------------------------------------------------------------------
