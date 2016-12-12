local oo        = require "oil.oo"
local Exception = require "oil.Exception"
local assert    = require "oil.assert"
local giop      = require "oil.corba.giop"                                      --[[VERBOSE]] local verbose = require "oil.verbose"

module("oil.corba.giop.Exception", oo.class)

__concat   = Exception.__concat
__tostring = Exception.__tostring

minor_code_value = 0
completion_status = 2

function __init(self, except, ...)
	if except then
		local sysex = giop.SystemExceptionIDs[ except[1] ]
		if sysex then
			except[1] = sysex
			except.exception_id = sysex
		end
	end
	return Exception.__init(self, except, ...)
end

assert.Exception = _M -- use GIOP exception as the default exception
