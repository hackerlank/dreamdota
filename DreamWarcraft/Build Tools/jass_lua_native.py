def want_skip(str):
    return False
#    return (str.find('Trigger') == 0 or str.find('LoadTrigger') == 0 or 'Timer' in str or 'Group' in str or 'Dialog' in str)

def parse_line(line):
#    if 'Hboolexpr' in line or 'condition' in line or 'action' in line:
#        return False

    jargs = ''
    jrv = ''
    jfun = line[0:line.find('(') - 1]

    if want_skip(jfun):
        return False

    jarg_start = line.find('(') + 1
    jarg_end = line.find(')')
    jargs_str = line[jarg_start:jarg_end]
    i, total = 0, len(jargs_str)
    while i < total:
        c = jargs_str[i]
        if (c == 'H'):
            i = jargs_str.find(';', i) + 1
            jargs = jargs + 'H'
        else:
            i = i + 1
            jargs = jargs + c
    
    jrv = line[line.find(')') + 1]

    alltypes = jrv + jargs
#    if 'C' in alltypes:
#        return False

    return {"rv" : jrv, "fun" : jfun, "args" : jargs}

def parse_file(file):
    lines = []
    f = open(file)
    for line in f.readlines():
        line = parse_line(line)
        if line:
            lines.append(line)
    f.close()
    return lines

def save_lua_prototype_code(lines, filename):
    file = open(filename, 'w')
    code = ''
    i, total = 0, len(lines)
    while i < total:
        f = lines[i]
        code = code + ('int JASS_%s(lua_State* L);\n' % (f['fun']))
        i = i + 1

    file.write(code)      
    file.close()


def get_lua_rv_code(t, call):
    if t == 'V':
        return call + ';'
    if t == 'I':
        return ('lua_pushinteger(L, %s);' % call)
    if t == 'R':
        return ('lua_pushnumber(L, %s);' % call)
    if t == 'H':
        return ('LUA_PUSHDWORD(L, %s);' % call)
    if t == 'S':
        return ('lua_pushstring(L, %s);' % call)
    if t == 'B':
        return ('lua_pushboolean(L, %s ? 1 : 0);' % call)
    if t == 'C':
        return ('LUA_PUSHDWORD(L, %s);' % call)

def get_lua_arg_code(t, i):
    if t == 'I':
        return ('int a%d = lua_tointeger(L, %d);' % (i, i + 1))
    if t == 'R':
        return ('lua_Number a%d = lua_tonumber(L, %d);' % (i, i + 1))
    if t == 'H':
        return ('DWORD a%d = LUA_TODWORD(L, %d);' % (i, i + 1))
    if t == 'S':
        return ('const char* a%d = lua_tostring(L, %d);' % (i, i + 1))
    if t == 'B':
        return ('bool a%d = lua_toboolean(L, %d) > 0;' % (i, i + 1))
    if t == 'C':
        return ('DWORD a%d = LUA_TODWORD(L, %d);' % (i, i + 1))

def save_lua_impl_code(lines, filename):
    file = open(filename, 'w')
    code = ''
    i, total = 0, len(lines)
    while i < total:
        f = lines[i]
        code = code + ('int JASS_%s(lua_State* L) {' % (f['fun']))
        code = code + ('if (lua_gettop(L) != %d) return 0;' % len(f['args']))
        args_code = '';
        if f['args']:
            a = []
            for ai in range(len(f['args'])):
                if f['args'][ai] == 'R':
                    a.append('(float)a' + str(ai))
                else:
                    a.append('a' + str(ai))
                args_code = args_code + get_lua_arg_code(f['args'][ai], ai)
            args = ', '.join(a)
        else:
            args = ''
        code = code + args_code;
        code = code + get_lua_rv_code(f['rv'], '%s(%s)' % ('JASS_WRAPPER_' + f['fun'], args))
        if f['rv'] == 'V':
            code = code + 'return 0;'
        else:
            code = code + 'return 1;'
        code = code + '}\n'
        i = i + 1

    file.write(code)      
    file.close()

def save_lua_prototype_data_code(lines, filename):
    file = open(filename, 'w')
    code = 'static const struct luaL_reg reg [] = {\n'
    i, total = 0, len(lines)
    while i < total:
        f = lines[i]
        code = code + ('\t{"%s", JASS_%s},' % (f['fun'], f['fun']))
        i = i + 1
    code = code + '\t{NULL, NULL}\n};'
    file.write(code)      
    file.close()

def save_lua_reg_code(lines, filename):
    file = open(filename, 'w')
    code = ''
    i, total = 0, len(lines)
    while i < total:
        f = lines[i]
        code = code + ('lua_register(L, "%s", JASS_%s);\n' % (f['fun'], f['fun']))
        i = i + 1
    file.write(code)      
    file.close()

def get_rv_fullname(t):
    if t == 'V':
        return 'void'
    if t == 'I':
        return 'integer'
    if t == 'R':
        return 'real'
    if t == 'H':
        return 'handle'
    if t == 'S':
        return 'DWORD'
    if t == 'B':
        return 'bool'

def get_arg_fullname(t):
    if t == 'I':
        return 'integer'
    if t == 'R':
        return 'float*'
    if t == 'H':
        return 'handle'
    if t == 'S':
        return 'string'
    if t == 'B':
        return 'bool'
    if t == 'C':
        return 'DWORD'

def get_wrapper_fullname(t):
    if t == 'V':
        return 'void'
    if t == 'I':
        return 'int'
    if t == 'R':
        return 'float'
    if t == 'H':
        return 'DWORD'
    if t == 'S':
        return 'const char*'
    if t == 'B':
        return 'bool'
    if t == 'C':
        return 'DWORD'    

def get_arg_code(t, i):
    if t == 'V':
        return ''
    if t == 'I':
        return 'a' + str(i)
    if t == 'R':
        return '&a' + str(i)
    if t == 'H':
        return 'a' + str(i)
    if t == 'S':
        return 'STR_TO_JASSSTR(a' + str(i) + ')'
    if t == 'B':
        return 'a' + str(i)
    if t == 'C':
        return 'a' + str(i)

def save_jass_prototype_code(lines, filename):
    file = open(filename, 'w')
    code = ''
    i, total = 0, len(lines)
    while i < total:
        f = lines[i]
        
        if f['args']:
            a = []
            for ai in range(len(f['args'])):
                a.append(get_arg_fullname(f['args'][ai]))
            args = ', '.join(a)
        else:
            args = 'void'
        code = code + ('typedef %s (*JASS_PROTOTYPE_%s)(%s);\n' % (get_rv_fullname(f['rv']), f['fun'], args))
        code = code + ('extern JASS_PROTOTYPE_%s JASS_NATIVE_%s;\n' % (f['fun'], f['fun']))
        i = i + 1
    file.write(code)      
    file.close()

def save_jass_native_code(lines, filename):
    file = open(filename, 'w')
    code = ''
    i, total = 0, len(lines)
    while i < total:
        f = lines[i]
        
        if f['args']:
            a = []
            for ai in range(len(f['args'])):
                a.append(get_arg_fullname(f['args'][ai]))
            args = ', '.join(a)
        else:
            args = 'void'
        code = code + ('JASS_PROTOTYPE_%s JASS_NATIVE_%s;\n' % (f['fun'], f['fun']))
        i = i + 1
    file.write(code)      
    file.close()    

def save_jass_wrapper_prototype(lines, filename):
    file = open(filename, 'w')
    code = ''
    i, total = 0, len(lines)
    while i < total:
        f = lines[i]
        
        if f['args']:
            a = []
            for ai in range(len(f['args'])):
                a.append(get_wrapper_fullname(f['args'][ai]))
            args = ', '.join(a)
        else:
            args = 'void'
        alltypes = f['rv'] + f['args']
        if 'S' in alltypes or 'R' in alltypes:
            code = code + ('%s JASS_WRAPPER_%s(%s);\n' % (get_wrapper_fullname(f['rv']), f['fun'], args))
        else:
            code = code + ('#define JASS_WRAPPER_%s JASS_NATIVE_%s\n' % (f['fun'], f['fun']))
        i = i + 1
    file.write(code)      
    file.close()

def save_jass_wrapper_impl(lines, filename):
    file = open(filename, 'w')
    code = ''
    i, total = 0, len(lines)
    while i < total:
        f = lines[i]
        alltypes = f['rv'] + f['args']
        if 'S' in alltypes or 'R' in alltypes:
            argcode = ''
            if f['args']:
                a = []
                a_call = []
                for ai in range(len(f['args'])):
                    a.append(get_wrapper_fullname(f['args'][ai]) + ' a' + str(ai))
                    a_call.append(get_arg_code(f['args'][ai], ai))
                args = ', '.join(a)
                args_call = ', '.join(a_call)
            else:
                args = ''
                args_call = ''
            
            code = code + ('%s JASS_WRAPPER_%s(%s) {\n' % (get_wrapper_fullname(f['rv']), f['fun'], args))
            rvtype = f['rv']
            if 'S' == rvtype:
                code = code + ('\t%s rv = JASSSTR_TO_STR(JASS_NATIVE_%s(%s));\n' % (get_wrapper_fullname(rvtype), f['fun'], args_call))
            elif 'R' == rvtype:
                code = code + ('\t%s rv = JASS_FLOAT_CAST(JASS_NATIVE_%s(%s));\n' % (get_wrapper_fullname(rvtype), f['fun'], args_call))
            else:
                if rvtype == 'V':
                    code = code + ('\tJASS_NATIVE_%s(%s);\n' % (f['fun'], args_call))
                else:
                    code = code + ('\t%s rv = JASS_NATIVE_%s(%s);\n' % (get_wrapper_fullname(rvtype), f['fun'], args_call))
            if 'S' in f['args']:
                code = code + '\tJASS_STR_CLEANUP();\n';
            if rvtype != 'V':
                code = code + '\treturn rv;\n';
            code = code + '}\n\n'
        i = i + 1
    file.write(code)      
    file.close()

def save_jass_bridge_code(lines, filename):
    file = open(filename, 'w')
    code = ''
    i, total = 0, len(lines)
    while i < total:
        f = lines[i]
        args_def = str(f['args'])
        if f['args']:
            a = []
            a_call = []
            for ai in range(len(args_def)):
                arg_item = (get_wrapper_fullname(args_def[ai]) + ' a' + str(ai))
                a.append(arg_item)
                a_call.append('a' + str(ai))
            args = ', '.join(a)
            args_call = ', '.join(a_call)
        else:
            args = 'void'
            args_call = ''
        code = code + ('inline %s %s(%s) {' % (get_wrapper_fullname(f['rv']), f['fun'], args))
        if f['rv'] == 'V':
            code = code + ('JASS_WRAPPER_%s(%s);' % (f['fun'], args_call))
        else:
            code = code + ('return JASS_WRAPPER_%s(%s);' % (f['fun'], args_call))
        code = code + '}\n'
        i = i + 1
    file.write(code)      
    file.close()

def save_lua_code(lines, filename):
    file = open(filename, 'w')
    code = ''
    i, total = 0, len(lines)
    while i < total:
        f = lines[i]
        
        if f['args']:
            a = []
            for ai in range(len(f['args'])):
                a.append(get_wrapper_fullname(f['args'][ai] + ' a' + str(ai)))
            args = ', '.join(a)
        else:
            args = 'void'
        code = code + ('inline %s %s(%s);\n' % (get_wrapper_fullname(f['rv']), f['fun'], args))
        i = i + 1
    file.write(code)      
    file.close()    

if __name__ == '__main__':
    lines = parse_file('JassNatives.txt')
    save_lua_prototype_data_code(lines, '../JassLuaNativesData.h.inc')
    save_lua_prototype_code(lines, '../JassLuaNatives.h.inc')
    save_lua_reg_code(lines, '../JassLuaNatives.reg.inc')
    save_lua_impl_code(lines, '../JassLuaNatives.impl.inc')
    save_jass_prototype_code(lines, '../JassNatives.prototype.inc')
    save_jass_wrapper_prototype(lines, '../JassNativesWrapper.h.inc')
    save_jass_wrapper_impl(lines, '../JassNativesWrapper.impl.inc')
    save_jass_bridge_code(lines, '../JassNativesBridge.inc')
    save_jass_native_code(lines, '../JassNativesImpl.inc')
