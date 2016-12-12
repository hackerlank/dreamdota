local alien = require "alien"
local crt = alien.load "msvcrt.dll"

msvcrt = {}

msvcrt.strlen = crt.strlen
msvcrt.strlen:types{"pointer", abi = "cdecl", ret = "ulong"}

msvcrt.strcpy = crt.strcpy
msvcrt.strcpy:types{"pointer", "pointer", abi = "cdecl", ret = "string"}

msvcrt.strcmp = crt.strcmp
msvcrt.strcmp:types{"pointer", "pointer", abi = "cdecl", ret = "long"}
