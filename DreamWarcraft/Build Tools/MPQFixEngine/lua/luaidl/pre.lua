--
-- Project:  LuaIDL
-- Author:   Ricardo Cosme <rcosme@tecgraf.puc-rio.br>
-- Filename: pre.lua
--

local error  = error
local io     = require "io"
local os     = require "os"
local ipairs = ipairs
local pairs  = pairs
local string = require "string"
local table  = require "table"
local type   = type

module 'luaidl.pre'

local tab_macros
local currNumLine
local currFilename = ""
local isProcessing
local homedir
local incpath
local tab_options

local scanner

---
-- Tower of Hanoi
-------------------------------------------------------------
local function newStack()
  return {""}
end

local function addString(stack, s)
  table.insert(stack, s)
  for i = (#stack - 1), 1, -1 do
    if (string.len(stack[i]) > string.len(stack[i+1])) then
      break
    end
    stack[i] = stack[i]..table.remove(stack)
  end
end
-------------------------------------------------------------

local function processDirective(...)
  local directive, macro, value = ...
  if (directive == "endif") then
    isProcessing = true
    return ''
  end
  if (isProcessing) then
    if (directive == "define") then
      tab_macros[macro] = value
    elseif (directive == "include") then
      local incFilename = string.sub(macro, 2, -2)
      local path = homedir..incFilename
      local fh, msg = io.open(path)
      if not fh then
        for _, v in ipairs(incpath) do
          path = v..'/'..incFilename
          fh, msg = io.open(path)
          if fh then
            break
          end
        end
      end
      if not fh then
        error(msg, 2)
      end
      local incSource = fh:read('*a')
      local incENDNumLine = currNumLine + 1
      local OUTFilename = currFilename
      incSource = scanner(incSource, tab_options)
      return string.format('# %d "%s" 1\n%s# %d "%s" 2\n',
                            1, path,
                            incSource,
                            incENDNumLine, OUTFilename
                         )
    elseif (directive == "ifndef") then
      if (tab_macros[macro]) then
        isProcessing = false
      end
    else
      return '#'..table.concat({...}, ' ')
    end
  end
  return ''
end

local function macroExpansion(str)
  for name, value in pairs(tab_macros) do
    str = string.gsub(str, '([^%w])'..name..'([^%w])', '%1'..value..'%2')
  end
  return str
end

function scanner(source, ptab_options)
  local output = newStack()
  local numLine
  if (not homedir) then
    addString(output, '# 1 "'..currFilename..'"\n')
    homedir, numLine = string.gsub(currFilename, '(.*/).*', '%1')
    if (numLine == 0) then
      homedir = ''
    end
  end
  numLine = 1
  -- ugly!
  source = source..'\n'
  for strLine in string.gfind(source, "(.-\n)") do
    strLine = string.gsub(strLine, "^%s*#%s*(%w+)%s*([^%s]*)%s*([^%s]*)", processDirective)
    if (isProcessing) then
      strLine = macroExpansion(strLine)
      addString(output, strLine)
    end
    numLine = numLine + 1
    currNumLine = numLine
  end
  return table.concat(output)
end

function run(source, ptab_options)
  tab_macros = {}
  currNumLine = 1
  isProcessing = true
  homedir = nil
  incpath = nil
  tab_options = ptab_options
  if tab_options then
    currFilename = tab_options.filename
    if currFilename then
      if (type(currFilename) ~= "string") then
        error("Invalid filename", 2)
      end
    else
      currFilename = ""
    end
    incpath = tab_options.incpath
    if incpath then
      if (type(incpath) ~= "table") then
        error("'incpath' must be a table", 2)
      end
    else
      incpath = {}
    end
  end
  return scanner(source, tab_options)
end
