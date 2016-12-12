--
-- Project:  LuaIDL
-- Author:   Ricardo Cosme <rcosme@tecgraf.puc-rio.br>
-- Filename: sin.lua
--

-- OMG IDL Grammar (Corba v3.0)
-- LL(1)
--(1)  <specification>          :=    <import_l> <definition_l>
--(2)  <import_l>               :=    <import> <import_l>
--(3)                           |     empty
--(4)  <import>                 :=    TK_IMPORT <imported_scope> ";"
--(5)  <imported_scope>         :=    <scoped_name>
--(6)                           |     TK_STRING_LITERAL
--(7)  <scoped_name>            :=    TK_ID <scoped_name>
--(8)                           |     ":" ":" TK_ID <scoped_name_l>
--(9)  <scoped_name_l>          :=    ":" ":" TK_ID <scoped_name_l>
--(10)                          |     empty
--(11)  <definition_l>          :=    <definition> <definition_l_r>
--(12)  <definition_l_r>        :=    <definition> <definition_l_r>
--(13)                          |     empty
--(14)  <definition>            :=    <type_dcl> ";"
--(15)                          |     <const_dcl> ";"
--(16)                          |     <except_dcl> ";"
--(17)                          |     <inter_value_event> ";"
--(18)                          |     <module> ";"
--(19)                          |     <type_id_dcl> ";"
--(20)                          |     <type_prefix_dcl> ";"
--(21)                          |     <component> ";"
--(22)                          |     <home_dcl> ";"
--(23)  <type_dcl>              :=    "typedef" <type_declarator>
--(24)                          |     <enum_type>
--(25)                          |     TK_NATIVE TK_ID
--(26)                          |     <union_or_struct>
--(27)  <type_declarator>       :=    <type_spec> <declarator_l>
--(28)  <type_spec>             :=    <simple_type_spec>
--(29)                          |     <constr_type_spec>
--(30)  <simple_type_spec>      :=    <base_type_spec>
--(31)                          |     <template_type_spec>
--(32)                          |     <scoped_name>
--(33)  <constr_type_spec>      :=    <struct_type>
--(34)                          |     <union_type>
--(35)                          |     <enum_type>
--(36)  <base_type_spec>        :=    <float_type_or_int_type>
--(37)                          |     TK_CHAR
--                              |     TK_WCHAR **
--(38)                          |     TK_BOOLEAN
--(39)                          |     TK_OCTET
--(40)                          |     TK_ANY
--(41)                          |     TK_OBJECT
--(42)                          |     TK_VALUEBASE
--(43)  <float_type_or_int_type>:=    <floating_pt_type>
--(44)                          |     <integer_type>
--(45)                          |     TK_LONG <long_or_double>
--(46)  <floating_pt_type>      :=    TK_FLOAT
--(47)                          |     TK_DOUBLE
--(48)  <integer_type>          :=    TK_SHORT
--(49)                          |     <unsigned_int>
--(50)  <unsigned_int>          :=    TK_UNSIGNED <unsigned_int_tail>
--(51)  <unsigned_int_tail>     :=    TK_LONG <long_e>
--(52)                          |     TK_SHORT
--(53)  <long_e>                :=    TK_LONG
--(54)                          |     empty
--(55)  <long_or_double>        :=    TK_LONG
--(56)                          |     TK_DOUBLE
--(57)                          |     empty
--(58)  <template_type_spec>    :=    <sequence_type>
--(59)                          |     <string_type>
--                              |     <wide_string_type> **
--(60)                          |     <fixed_pt_type>
--(61)  <sequence_type>         :=    TK_SEQUENCE "<" <simple_type_spec> <sequence_type_tail>
--(69)  <sequence_type_tail>    :=    "," <positive_int_const> ">"
--(70)                          |     ">"
--(71)  <string_type>           :=    TK_STRING <string_type_tail>
--(72)  <string_type_tail>      :=    "<" <positive_int_const> ">"
--(73)                          |     empty
--    <wide_string_type>        :=    TK_WSTRING <string_type_tail> **
--(74)  <fixed_pt_type>         :=    TK_FIXED "<" <positive_int_const> "," <positive_int_const> ">"
--(75)  <positive_int_const>    :=    <xor_expr> <or_expr_l>
--(91)  <or_expr_l>             :=    "|" <xor_expr> <or_expr_l>
--(92)                          |     empty
--(93)  <xor_expr>              :=    <and_expr> <xor_expr_l>
--(94)  <xor_expr_l>            :=    "^" <and_expr> <xor_expr_l>
--(95)                          |     empty
--(96)  <and_expr>              :=    <shift_expr> <and_expr_l>
--(97)  <and_expr_l>            :=    "&" <shift_expr> <and_expr_l>
--(98)                          |     empty
--(99)  <shift_expr>            :=    <add_expr> <shift_expr_l>
--(100) <shift_expr_l>          :=    ">>" <add_expr> <shift_expr_l>
--(101)                         |     "<<" <add_expr> <shift_expr_l>
--(102)                         |     empty
--(103) <add_expr>              :=    <mult_expr> <add_expr_l>
--(104) <add_expr_l>            :=    "+" <mult_expr> <add_expr_l>
--(105)                         |     "-" <mult_expr> <add_expr_l>
--(106)                         |     empty
--(107) <mult_expr>             :=    <unary_expr> <mult_expr_l>
--(108) <mult_expr_l>           :=    "*" <unary_expr> <mult_expr_l>
--(109)                         |     "/" <unary_expr> <mult_expr_l>
--(110)                         |     "%" <unary_expr> <mult_expr_l>
--(111)                         |     empty
--(112) <unary_expr>            :=    <unary_operator> <primary_expr>
--(113)                         |     <primary_expr>
--(114) <unary_operator>        :=    "-"
--(115)                         |     "+"
--(116)                         |     "~"
--(117) <primary_expr>          :=    <scoped_name>
--(118)                         |     <literal>
--(119)                         |     "(" <positive_int_const3> ")"
--(120) <literal>               :=    TK_INTEGER_LITERAL
--(121)                         |     TK_STRING_LITERAL
--                              |     TK_WSTRING_LITERAL **
--(122)                         |     TK_CHAR_LITERAL
--                              |     TK_WCHAR_LITERAL **
--(123)                         |     TK_FIXED_LITERAL
--(124)                         |     TK_FLOAT_LITERAL
--(125)                         |     <boolean_literal>
--(126) <boolean_literal>       :=    TK_TRUE
--(127)                         |     TK_FALSE
--(136) <struct_type>           :=    TK_STRUCT TK_ID "{" <member_l> "}"
--(137) <member_l>              :=    <member> <member_r>
--(138) <member_r>              :=    <member> <member_r>
--(139)                         |     empty
--(140) <member>                :=    <type_spec> <declarator_l> ";"
--(141) <typedef_dcl_l>         :=    <typedef_dcl> <typedef_l_r>
--(142) <typedef_l_r>           :=    "," <typedef_dcl> <typedef_l_r>
--(143)                         |     empty
--(144) <typedef_dcl>           :=    TK_ID <fixed_array_size_l>
--(145) <fixed_array_size_l>    :=    <fixed_array_size> <fixed_array_size_l>
--(146)                         |     empty
--(147) <fixed_array_size>      :=    "[" <positive_int_const4> "]"
--(148) <union_type>            :=    TK_UNION TK_ID TK_SWITCH "(" <switch_type_spec> ")"
--                                    "{" <case_l> "}"
--(149) <switch_type_spec>      :=    <integer_type>
--(150)                         |     TK_LONG <long_e>
--(151)                         |     TK_CHAR
--(152)                         |     TK_BOOLEAN
--(153)                         |     TK_ENUM
--(154)                         |     <scoped_name>
--(155) <case_l>                :=    <case> <case_l_r>
--(156) <case_l_r>              :=    <case> <case_l_r>
--(157)                         |     empty
--(158) <case>                  :=    <case_label_l> <element_spec> ";"
--(159) <case_label_l>          :=    <case_label> <case_label_l_r>
--(160) <case_label_l_r>        :=    <case_label> <case_label_l_r>
--(161)                         |     empty
--(162) <case_label>            :=    TK_CASE <positive_int_const5> ":"
--(163)                         |     TK_DEFAULT ":"
--(164) <element_spec>          :=    <type_spec> <declarator>
--(165) <enum_type>             :=    TK_ENUM <enumerator>
--                                    "{" <enumerator> <enumerator_l> "}"
--(166) <enumerator_l>          :=    "," <enumerator> <enumerator_l>
--(167)                         |     empty
--(168) <union_or_struct>       :=    TK_STRUCT TK_ID <struct_tail>
--(169)                         |     TK_UNION TK_ID TK_SWITCH <union_tail>
--(170) <struct_tail>           :=    "{" <member_l> "}"
--(171)                         |     empty
--(172) <union_tail>            :=    TK_SWITCH "(" <switch_type_spec> ")"
--                                    "{" <case_l> "}"
--(173)                         |     empty
--(174) <const_dcl>             :=    TK_CONST <const_type> TK_ID "=" <positive_int_const>
--(175) <const_type>            :=    <float_type_or_int_type>
--(176)                         |     TK_CHAR
--                              |     TK_WCHAR **
--(177)                         |     TK_BOOLEAN
--(178)                         |     TK_STRING
--                              |     TK_WSTRING **
--(179)                         |     <scoped_name>
--(180)                         |     TK_OCTET
--(181)                         |     TK_FIXED
--(186) <except_dcl>            :=    TK_EXCEPTION TK_ID "{" <member_l_empty> "}"
--(187) <member_l_empty>        :=    <member> <member_l_empty>
--(188)                         |     empty
--(189) <inter_value_event>     :=    TK_ABSTRACT <abstract_tail>
--(190)                         |     TK_LOCAL TK_INTERFACE TK_ID <interface_tail>
--(191)                         |     TK_CUSTOM <value_or_event>
--(192)                         |     TK_INTERFACE TK_ID <interface_tail>
--(193)                         |     TK_VALUETYPE TK_ID <value_tail>
--(194)                         |     TK_EVENTTYPE TK_ID <eventtype_tail>
--(195) <abstract_tail>         :=    TK_INTERFACE TK_ID <interface_tail>
--(196)                         |     TK_VALUETYPE TK_ID <valueinhe_export_empty>
--(197)                         |     TK_EVENTTYPE TK_ID <valueinhe_export_empty>
--(198) <interface_tail>        :=    ":" <scoped_name> <bases> "{" <export_l> "}"
--(199)                         |     "{" <export_l> "}"
--(200)                         |     empty
--(205) <bases>                 :=    "," <scoped_name> <bases>
--(206)                         |     empty
--(207) <export_l>              :=    <export> <export_l>
--(208)                         |     empty
--(209) <export>                :=    <type_dcl> ";"
--(210)                         |     <const_dcl> ";"
--(211)                         |     <except_dcl> ";"
--(212)                         |     <attr_dcl> ";"
--(213)                         |     <op_dcl> ";"
--(214)                         |     <type_id_dcl> ";"
--(215)                         |     <type_prefix_dcl> ";"
--(216) <attr_dcl>              :=    <readonly_attr_spec>
--(217)                         |     <attr_spec>
--(218) <readonly_attr_spec>    :=    TK_READONLY TK_ATTRIBUTE <param_type_spec> <readonly_attr_dec>
--(219) <param_type_spec>       :=    <base_type_spec>
--(220)                         |     <string_type>
--                              |     <wide_string_type> **
--(221)                         |     <scoped_name>
--(226) <readonly_attr_dec>     :=    TK_ID <readonly_attr_dec_tail>
--(227) <readonly_attr_dec_tail>:=    <raises_expr>
--(228)                         |     <simple_dec_l>
--                              |     empty
--(229) <raises_expr>           :=    TK_RAISES "(" <scoped_name> <inter_name_seq> ")"
--(230) <simple_dec_l)          :=    "," TK_ID <simple_dec_l>
--(231)                         |     empty
--(232) <attr_spec>             :=    TK_ATTRIBUTE <param_type_spec> <attr_declarator>
--(233) <attr_declarator>       :=    TK_ID <attr_declarator_tail>
--(234) <attr_declarator_tail>  :=    <attr_raises_expr>
--(235)                         |     <simple_dec_l>
--                              |     empty
--(236) <attr_raises_expr>      :=    TK_GETRAISES <exception_l> <attr_raises_expr_tail>
--(237)                         |     TK_SETRAISES <exception_l>
--(238) <attr_raises_expr_tail> :=    TK_SETRAISES <exception_l>
--(239)                         |     empty
--(240) <exception_l>           :=    "(" <scoped_name> <inter_name_seq> ")"
--(241) <inter_name_seq>        :=    "," <scoped_name> <inter_name_seq>
--(242)                         |     empty
--(243) <op_dcl>                :=    TK_ONEWAY <op_type_spec> TK_ID <parameter_dcls> <raises_expr_e>
--                                    <context_expr_e>
--(244)                         |     <op_type_spec> TK_ID <parameter_dcls> <raises_expr_e>
--                                    <context_expr_e>
--(245) <op_type_spec>          :=    <param_type_spec>
--(246)                         |     TK_VOID
--(247) <parameter_dcls>        :=    "(" <parameter_dcls_tail>
--(248) <parameter_dcls_tail>   :=    <param_dcl> <param_dcl_l>
--(249)                         |     ")"
--(250) <param_dcl>             :=    <param_attribute> <param_type_spec> TK_ID
--(251) <param_attribute>       :=    TK_IN
--(252)                         |     TK_OUT
--(253)                         |     TK_INOUT
--(254) <param_dcl_l>           :=    "," <param_dcl> <param_dcl_l>
--(255)                         |     empty
--(256) <context_expr>          :=    TK_CONTEXT "(" <context> <string_literal_l> ")"
--(257) <string_literal_l>      :=    "," <context> <string_literal_l>
--(258)                         |     empty
--(259) <type_id_dcl>           :=    TK_TYPEID <scoped_name> TK_STRING_LITERAL
--(260) <type_prefix_dcl>       :=    TK_TYPEPREFIX <scoped_name> TK_STRING_LITERAL
--(265) <valueinhe_export_empty>:=    <value_inhe_spec> "{" <export_l> "}
--(266)                         |     "{" <export_l> "}"
--(267)                         |     empty
--(268) <value_inhe_spec>       :=    ":" <truncatable_e> <value_name> <value_name_list>
--                                    <supports_e>
--(269)                         |     <supports_e>
--(270)                         |     empty
--(271) <truncatable_e>         :=    TK_TRUNCATABLE
--(272)                         |     empty
--(273) <value_name>            :=    TK_ID <value_name_l>
--(274)                         |     ":" ":" TK_ID <value_name_l>
--(275) <value_name_l>          :=    ":" ":" TK_ID <value_name_l>
--(276)                         |     empty
--(277) <value_name_list>       :=    "," <value_name> <value_name_list>
--(278)                         |     empty
--(279) <supports_e>            :=    TK_SUPPORTS <inter_name> <inter_name_seq2>
--(280)                         |     empty
--(281) <value_or_event>        :=    TK_VALUETYPE TK_ID <valueinhe_export>
--(282)                         |     TK_EVENTTYPE TK_ID <valueinhe_export>
--(283) <valueinhe_export>      :=    <value_inhe_spec> "{" <value_element_l> "}"
--(284)                         |     "{" <value_element_l> "}"
--(285) <value_element_l>       :=    <value_element> <value_element_l>
--(286)                         |     empty
--(287) <value_element>         :=    <export>
--(288)                         |     <state_member>
--(289)                         |     <init_dcl>
--(290) <state_member>          :=    TK_PUBLIC <type_spec> <declarator_l> ";"
--(291)                         |     TK_PRIVATE <type_spec> <declarator_l> ";"
--(292) <init_dcl>              :=    TK_FACTORY TK_ID "(" <init_param_dcl_l_e> ")"
--                                    <raises_expr_e> ";"
--(293) <init_param_dcl_l_e>    :=    <init_param_dcl> <init_param_dcl_l_e_r>
--(294)                         |     empty
--(295) <init_param_dcl_l_e_r>  :=    "," <init_param_dcl> <init_param_dcl_l_e_r>
--(296)                         |     empty
--(297) <init_param_dcl>        :=    TK_IN <param_type_spec> TK_ID
--(298) <value_tail>            :=    <value_inhe_spec> "{" <value_element_l> "}"
--(299)                         |     "{" <value_element_l> "}"
--(300)                         |     <type_spec>
--(301)                         |     empty
--(302) <eventtype_tail>        :=    <value_inhe_spec> "{" <value_element_l> "}"
--(303)                         |     "{" <value_element_l> "}"
--(304)                         |     empty
--(305) <module>                :=    TK_MODULE TK_ID "{" <definition_l> "}"
--(306) <component>             :=    TK_COMPONENT TK_ID <component_tail>
--(307) <component_tail>        :=    <component_inh_spec> <supp_inter_spec>
--                                    "{" <component_body> "}"
--(308)                         |     <supp_inter_spec> "{" <component_body> "}"
--(309)                         |     "{" <component_body> "}"
--(310)                         |     empty
--(311) <component_inh_spec>    :=    ":" <component_name>
--(312) <component_name>        :=    TK_ID <component_name_l>
--(313)                         |     ":" ":" TK_ID <component_name_l>
--(314) <component_name_l>      :=    ":" ":" TK_ID <component_name_l>
--(315)                         |     empty
--(316) <supp_inter_spec>       :=    TK_SUPPORTS <supp_name> <supp_name_list>
--(316e)                        |     empty
--(317) <supp_name>             :=    TK_ID <supp_name_l>
--(318)                         |     ":" ":" TK_ID <supp_name_l>
--(319) <supp_name_l>           :=    ":" ":" TK_ID <supp_name_l>
--(320)                         |     empty
--(321) <supp_name_list>        :=    "," <supp_name> <supp_name_list>
--(322)                         |     empty
--(323) <component_body>        :=    <component_export> <component_body>
--(324)                         |     empty
--(325) <component_export>      :=    <provides_dcl> ";"
--(326)                         |     <uses_dcl> ";"
--(327)                         |     <emits_dcl> ";"
--(328)                         |     <publishes_dcl> ";"
--(329)                         |     <consumes_dcl> ";"
--(330)                         |     <attr_dcl> ";"
--(331) <provides_dcl>          :=    TK_PROVIDES <interface_type> TK_ID
--(332) <interface_type>        :=    <scoped_name>
--(333)                         |     TK_OBJECT
--(338) <uses_dcl>              :=    TK_USES <multiple_e> <interface_type> TK_ID
--(339) <multiple_e>            :=    TK_MULTIPLE
--(340)                         |     empty
--(341) <emits_dcl>             :=    TK_EMITS <scoped_name> TK_ID
--(342) <publishes_dcl>         :=    TK_PUBLISHES <scoped_name> TK_ID
--(343) <consumes_dcl>          :=    TK_CONSUMES <scoped_name> TK_ID

--(344) <home_dcl>              :=    TK_HOME TK_ID <home_dcl_tail>
--(345) <home_dcl_tail>         :=    <home_inh_spec> <supp_inter_spec>
--                                    TK_MANAGES <home_name> <primary_key_spec_e>
--                                    "{" <home_export_l> "}"raises_expr>
--(346)                         |     <supp_inter_spec> TK_MANAGES <home_name> <primary_key_spec_e>
--                                    "{" <home_export_l> "}"
--(347)                         |     TK_MANAGES <home_name> <primary_key_spec_e>
--                                    "{" <home_export_l> "}"
--(348) <home_inh_spec>         :=    ":" <scoped_name>
--(353) <primary_key_spec_e>    :=    TK_PRIMARYKEY <scoped_name>
--(354)                         |     empty
--(359) <home_export_l>         :=    <home_export> <home_export_l>
--(360)                         |     empty
--(361) <home_export>           :=    <export>
--(362)                         |     <factory_dcl> ";"
--(363)                         |     <finder_dcl> ";"
--(364) <factory_dcl>           :=    TK_FACTORY TK_ID "(" <init_param_dcls> ")"
--                                    <raises_expr_e>
--(365) <finder_dcl>            :=    TK_FINDER TK_ID "(" <init_param_dcls> ")"
--                                    <raises_expr_e>
--(366) <init_param_dcls>       :=    <init_param_dcl> <init_param_dcl_list>
--(367)                         |     empty
--(368) <init_param_dcl_list>   :=    "," <init_param_dcl> <init_param_dcl_list>
--(369)                         |     empty
--(370) <raises_expr_e>         :=    <raises_expr>
--(371)                         |     empty
--(376) <enumerator>            :=    TK_ID
--(377) <context_expr_e>        :=    <context_expr>
--(378)                         |     empty
--(379) <context>               :=    TK_STRING_LITERAL

local type     = type
local pairs    = pairs
local tonumber = tonumber
local require  = require
local error    = error
local ipairs   = ipairs

local math     = require "math"
local string   = require "string"
local table    = require "table"

module 'luaidl.sin'

local lex = require 'luaidl.lex'

local tab_firsts = {}
local tab_follow = {}

local function set_firsts(firsts)
  local tab = {}
  for _, token in ipairs(firsts) do
    local tokenDcl = lex.tab_tokens[token]
    if tokenDcl then
      tab[tokenDcl] = true
    else
      tab[token] = true
    end
  end
  return tab
end

tab_firsts.rule_1   = set_firsts { 'TK_IMPORT' }
tab_firsts.rule_11  = set_firsts {
  'TK_TYPEDEF','TK_ENUM','TK_NATIVE','TK_UNION','TK_STRUCT',
  'TK_CONST','TK_EXCEPTION','TK_ABSTRACT','TK_LOCAL',
  'TK_INTERFACE','TK_CUSTOM','TK_VALUETYPE',
  'TK_EVENTTYPE','TK_MODULE','TK_TYPEID',
  'TK_TYPEPREFIX','TK_COMPONENT','TK_HOME'
}
tab_firsts.rule_12  = tab_firsts.rule_11
tab_firsts.rule_14  = set_firsts { 'TK_TYPEDEF', 'TK_ENUM', 'TK_NATIVE', 'TK_UNION', 'TK_STRUCT' }
tab_firsts.rule_15  = set_firsts { 'TK_CONST' }
tab_firsts.rule_16  = set_firsts { 'TK_EXCEPTION' }
tab_firsts.rule_17  = set_firsts {
  'TK_ABSTRACT', 'TK_LOCAL', 'TK_INTERFACE', 'TK_CUSTOM',
  'TK_VALUETYPE', 'TK_EVENTTYPE'
}
tab_firsts.rule_18  = set_firsts { 'TK_MODULE' }
tab_firsts.rule_19  = set_firsts { 'TK_TYPEID' }
tab_firsts.rule_20  = set_firsts { 'TK_TYPEPREFIX' }
tab_firsts.rule_21  = set_firsts { 'TK_COMPONENT' }
tab_firsts.rule_22  = set_firsts { 'TK_HOME' }
tab_firsts.rule_23  = set_firsts { 'TK_TYPEDEF' }
tab_firsts.rule_24  = set_firsts { 'TK_ENUM' }
tab_firsts.rule_25  = set_firsts { 'TK_NATIVE' }
tab_firsts.rule_26  = set_firsts { 'TK_STRUCT', 'TK_UNION' }
tab_firsts.rule_27  = set_firsts {
  'TK_CHAR', 'TK_BOOLEAN', 'TK_OCTET', 'TK_ANY', 'TK_OBJECT',
  'TK_VALUEBASE', 'TK_LONG', 'TK_FLOAT', 'TK_DOUBLE', 'TK_SHORT',
  'TK_UNSIGNED', 'TK_SEQUENCE' , 'TK_STRING', 'TK_FIXED' ,
  'TK_ID', ":", 'TK_STRUCT', 'TK_UNION', 'TK_ENUM',
}
tab_firsts.rule_28  = set_firsts {
  'TK_CHAR', 'TK_BOOLEAN', 'TK_OCTET', 'TK_ANY', 'TK_OBJECT',
  'TK_VALUEBASE', 'TK_LONG', 'TK_FLOAT', 'TK_DOUBLE', 'TK_SHORT',
  'TK_UNSIGNED', 'TK_SEQUENCE' , 'TK_STRING', 'TK_FIXED' ,
  'TK_ID', ":",
}
tab_firsts.rule_29  = set_firsts { 'TK_STRUCT', 'TK_UNION', 'TK_ENUM' }
tab_firsts.rule_30  = set_firsts {
  'TK_CHAR', 'TK_BOOLEAN', 'TK_OCTET', 'TK_ANY', 'TK_OBJECT',
  'TK_VALUEBASE', 'TK_LONG', 'TK_FLOAT', 'TK_DOUBLE', 'TK_SHORT',
  'TK_UNSIGNED',
}
tab_firsts.rule_31  = set_firsts { 'TK_SEQUENCE', 'TK_STRING', 'TK_FIXED' }
tab_firsts.rule_32  = set_firsts { 'TK_ID', ':' }

tab_firsts.rule_33  = set_firsts { 'TK_STRUCT' }
tab_firsts.rule_34  = set_firsts { 'TK_UNION' }
tab_firsts.rule_35  = set_firsts { 'TK_ENUM' }
tab_firsts.rule_36  = set_firsts { 'TK_FLOAT', 'TK_DOUBLE', 'TK_SHORT', 'TK_UNSIGNED', 'TK_LONG' }
tab_firsts.rule_37  = set_firsts { 'TK_CHAR' }
tab_firsts.rule_38  = set_firsts { 'TK_BOOLEAN' }
tab_firsts.rule_39  = set_firsts { 'TK_OCTET' }
tab_firsts.rule_40  = set_firsts { 'TK_ANY' }
tab_firsts.rule_41  = set_firsts { 'TK_OBJECT' }
tab_firsts.rule_42  = set_firsts { 'TK_VALUEBASE' }

tab_firsts.rule_43  = set_firsts { 'TK_FLOAT', 'TK_DOUBLE' }
tab_firsts.rule_44  = set_firsts { 'TK_SHORT', 'TK_UNSIGNED' }
tab_firsts.rule_45  = set_firsts { 'TK_LONG' }
tab_firsts.rule_46  = set_firsts { 'TK_FLOAT' }
tab_firsts.rule_47  = set_firsts { 'TK_DOUBLE' }
tab_firsts.rule_48  = set_firsts { 'TK_SHORT' }
tab_firsts.rule_49  = set_firsts { 'TK_UNSIGNED' }
tab_firsts.rule_50  = tab_firsts.rule_49
tab_firsts.rule_51  = tab_firsts.rule_45
tab_firsts.rule_52  = set_firsts { 'TK_SHORT' }
tab_firsts.rule_53  = set_firsts { 'TK_LONG' }
tab_firsts.rule_55  = set_firsts { 'TK_LONG' }
tab_firsts.rule_56  = set_firsts { 'TK_DOUBLE' }

tab_firsts.rule_58  = set_firsts { 'TK_SEQUENCE' }
tab_firsts.rule_59  = set_firsts { 'TK_STRING' }
tab_firsts.rule_60  = set_firsts { 'TK_FIXED' }

tab_firsts.rule_62  = tab_firsts.rule_30
tab_firsts.rule_63  = tab_firsts.rule_31
tab_firsts.rule_64  = tab_firsts.rule_32

tab_firsts.rule_69  = set_firsts { ',' }
tab_firsts.rule_70  = set_firsts { '>' }
tab_firsts.rule_72  = set_firsts { '<' }
tab_firsts.rule_75  = set_firsts {
  '-', '+', '~', '(', 'TK_ID', ':', 'TK_INTEGER_LITERAL',
  'TK_STRING_LITERAL', 'TK_CHAR_LITERAL', 'TK_FIXED_LITERAL',
  'TK_FLOAT_LITERAL', 'TK_TRUE', 'TK_FALSE'
}
tab_firsts.rule_93   = tab_firsts.rule_75
tab_firsts.rule_91   = set_firsts { '|' }
tab_firsts.rule_94   = set_firsts { '^' }
tab_firsts.rule_96   = tab_firsts.rule_75
tab_firsts.rule_97   = set_firsts { '&' }
tab_firsts.rule_99   = tab_firsts.rule_75
tab_firsts.rule_100  = set_firsts { '>>' }
tab_firsts.rule_101  = set_firsts { '<<' }
tab_firsts.rule_103  = tab_firsts.rule_75
tab_firsts.rule_104  = set_firsts { '+' }
tab_firsts.rule_105  = set_firsts { '-' }
tab_firsts.rule_107  = tab_firsts.rule_75
tab_firsts.rule_108  = set_firsts { '*' }
tab_firsts.rule_109  = set_firsts { '/' }
tab_firsts.rule_110  = set_firsts { '%' }
tab_firsts.rule_112  = set_firsts { '-', '+', '~' }
tab_firsts.rule_113  = set_firsts {
  '(', 'TK_ID', ':', 'TK_INTEGER_LITERAL',
  'TK_STRING_LITERAL', 'TK_CHAR_LITERAL', 'TK_FIXED_LITERAL',
  'TK_FLOAT_LITERAL', 'TK_TRUE', 'TK_FALSE'
}
tab_firsts.rule_114  = set_firsts { '-' }
tab_firsts.rule_115  = set_firsts { '+' }
tab_firsts.rule_116  = set_firsts { '~' }
tab_firsts.rule_117  = set_firsts { 'TK_ID', ':' }
tab_firsts.rule_118  = set_firsts {
  'TK_INTEGER_LITERAL', 'TK_STRING_LITERAL', 'TK_CHAR_LITERAL',
  'TK_FIXED_LITERAL', 'TK_FLOAT_LITERAL', 'TK_TRUE', 'TK_FALSE'
}
tab_firsts.rule_119  = set_firsts { '(' }
tab_firsts.rule_120  = set_firsts { 'TK_INTEGER_LITERAL' }
tab_firsts.rule_121  = set_firsts { 'TK_STRING_LITERAL' }
tab_firsts.rule_122  = set_firsts { 'TK_CHAR_LITERAL' }
tab_firsts.rule_123  = set_firsts { 'TK_FIXED_LITERAL' }
tab_firsts.rule_124  = set_firsts { 'TK_FLOAT_LITERAL' }
tab_firsts.rule_125  = set_firsts { 'TK_TRUE', 'TK_FALSE' }
tab_firsts.rule_126  = set_firsts { 'TK_TRUE' }
tab_firsts.rule_127  = set_firsts { 'TK_FALSE' }

tab_firsts.rule_137  = tab_firsts.rule_27
tab_firsts.rule_138  = tab_firsts.rule_137

tab_firsts.rule_140  = tab_firsts.rule_138
tab_firsts.rule_141  = set_firsts { 'TK_ID' }
tab_firsts.rule_142  = set_firsts { "," }

tab_firsts.rule_144  = tab_firsts.rule_141
tab_firsts.rule_145  = set_firsts { "[" }

tab_firsts.rule_147  = tab_firsts.rule_145
tab_firsts.rule_148  = set_firsts { 'TK_UNION' }
tab_firsts.rule_149  = tab_firsts.rule_44
tab_firsts.rule_150  = set_firsts { 'TK_LONG' }
tab_firsts.rule_151  = set_firsts { 'TK_CHAR' }
tab_firsts.rule_152  = set_firsts { 'TK_BOOLEAN' }
tab_firsts.rule_153  = set_firsts { 'TK_ENUM' }
tab_firsts.rule_154  = set_firsts { 'TK_ID', ':' }
tab_firsts.rule_155  = set_firsts { 'TK_CASE', 'TK_DEFAULT' }
tab_firsts.rule_156  = set_firsts { 'TK_CASE', 'TK_DEFAULT' }

tab_firsts.rule_158  = set_firsts { 'TK_CASE', 'TK_DEFAULT' }
tab_firsts.rule_159  = set_firsts { 'TK_CASE', 'TK_DEFAULT' }
tab_firsts.rule_160  = set_firsts { 'TK_CASE', 'TK_DEFAULT' }

tab_firsts.rule_162  = set_firsts { 'TK_CASE' }
tab_firsts.rule_163  = set_firsts { 'TK_DEFAULT' }
tab_firsts.rule_164  = tab_firsts.rule_27

tab_firsts.rule_166  = set_firsts { "," }

tab_firsts.rule_168  = set_firsts { 'TK_STRUCT' }
tab_firsts.rule_169  = set_firsts { 'TK_UNION' }
tab_firsts.rule_170  = set_firsts { '{' }

tab_firsts.rule_172  = set_firsts { 'TK_SWITCH' }

tab_firsts.rule_174  = set_firsts { 'TK_CONST' }
tab_firsts.rule_175  = tab_firsts.rule_36
tab_firsts.rule_176  = set_firsts { 'TK_CHAR' }
tab_firsts.rule_177  = set_firsts { 'TK_BOOLEAN' }
tab_firsts.rule_178  = set_firsts { 'TK_STRING' }
tab_firsts.rule_179  = set_firsts { 'TK_ID', ':' }
tab_firsts.rule_180  = set_firsts { 'TK_OCTET' }
tab_firsts.rule_181  = set_firsts { 'TK_FIXED' }
tab_firsts.rule_186  = set_firsts { 'TK_EXCEPTION' }
tab_firsts.rule_187  = tab_firsts.rule_137

tab_firsts.rule_189  = set_firsts { 'TK_ABSTRACT' }
tab_firsts.rule_190  = set_firsts { 'TK_LOCAL' }
tab_firsts.rule_191  = set_firsts { 'TK_CUSTOM' }
tab_firsts.rule_192  = set_firsts { 'TK_INTERFACE' }
tab_firsts.rule_193  = set_firsts { 'TK_VALUETYPE' }
tab_firsts.rule_194  = set_firsts { 'TK_EVENTTYPE' }
tab_firsts.rule_195  = set_firsts { 'TK_INTERFACE' }
tab_firsts.rule_196  = set_firsts { 'TK_VALUETYPE' }
tab_firsts.rule_198  = set_firsts { ':' }
tab_firsts.rule_199  = set_firsts { '{' }

tab_firsts.rule_207  = set_firsts { 'TK_ONEWAY', 'TK_VOID', 'TK_STRING', 'TK_ID', ':',
                        'TK_CHAR', 'TK_BOOLEAN', 'TK_OCTET', 'TK_ANY',
                        'TK_OBJECT', 'TK_VALUEBASE', 'TK_LONG', 'TK_FLOAT',
                        'TK_DOUBLE', 'TK_SHORT', 'TK_UNSIGNED','TK_TYPEDEF',
                        'TK_ENUM', 'TK_NATIVE', 'TK_UNION', 'TK_STRUCT',
                        'TK_EXCEPTION', 'TK_READONLY', 'TK_ATTRIBUTE', 'TK_CONST', -- 'TK_TYPECODE',
                       }

tab_firsts.rule_209  = tab_firsts.rule_14
tab_firsts.rule_210  = set_firsts { 'TK_CONST' } 
tab_firsts.rule_211  = set_firsts { 'TK_EXCEPTION' }
tab_firsts.rule_212  = set_firsts { 'TK_READONLY', 'TK_ATTRIBUTE' }
tab_firsts.rule_213  = set_firsts {
  'TK_ONEWAY', 'TK_VOID', 'TK_STRING', 'TK_ID', ':',
  'TK_CHAR', 'TK_BOOLEAN', 'TK_OCTET', 'TK_ANY',
  'TK_OBJECT', 'TK_VALUEBASE', 'TK_LONG', 'TK_FLOAT',
  'TK_DOUBLE', 'TK_SHORT', 'TK_UNSIGNED',
}

tab_firsts.rule_216  = set_firsts { 'TK_READONLY' }
tab_firsts.rule_217  = set_firsts { 'TK_ATTRIBUTE' }

tab_firsts.rule_219  = tab_firsts.rule_30
tab_firsts.rule_220  = set_firsts { 'TK_STRING' }
tab_firsts.rule_221  = tab_firsts.rule_32


tab_firsts.rule_227  = set_firsts { 'TK_RAISES' }
tab_firsts.rule_228  = set_firsts { ',' }

tab_firsts.rule_230  = set_firsts { 'TK_ID' }
tab_firsts.rule_234  = set_firsts { 'TK_GETRAISES', 'TK_SETRAISES' }
tab_firsts.rule_235  = set_firsts { ',' }
tab_firsts.rule_236  = set_firsts { 'TK_GETRAISES' }
tab_firsts.rule_237  = set_firsts { 'TK_SETRAISES' }
tab_firsts.rule_238  = tab_firsts.rule_237

tab_firsts.rule_243  = set_firsts { 'TK_ONEWAY' }
tab_firsts.rule_244  = set_firsts {
  'TK_VOID', 'TK_STRING', 'TK_ID', ':',
  'TK_CHAR', 'TK_BOOLEAN', 'TK_OCTET', 'TK_ANY',
  'TK_OBJECT', 'TK_VALUEBASE', 'TK_LONG', 'TK_FLOAT',
  'TK_DOUBLE', 'TK_SHORT', 'TK_UNSIGNED',
}
tab_firsts.rule_245  = set_firsts {
  'TK_CHAR', 'TK_BOOLEAN', 'TK_OCTET', 'TK_ANY', 'TK_OBJECT',
  'TK_VALUEBASE', 'TK_LONG', 'TK_FLOAT', 'TK_DOUBLE', 'TK_SHORT',
  'TK_UNSIGNED', 'TK_STRING', 'TK_ID', ":",
}
tab_firsts.rule_246  = set_firsts { 'TK_VOID' }

tab_firsts.rule_248  = set_firsts { 'TK_IN', 'TK_OUT', 'TK_INOUT' }
tab_firsts.rule_249  = set_firsts { ')' }

tab_firsts.rule_251  = set_firsts { 'TK_IN' }
tab_firsts.rule_252  = set_firsts { 'TK_OUT' }
tab_firsts.rule_253  = set_firsts { 'TK_INOUT' }
tab_firsts.rule_254  = set_firsts { ',' }

tab_firsts.rule_257  = set_firsts { ',' }

tab_firsts.rule_268  = set_firsts { ':' }
tab_firsts.rule_269  = set_firsts { 'TK_SUPPORTS' }
tab_firsts.rule_271  = set_firsts { 'TK_TRUNCATABLE' }
tab_firsts.rule_277  = set_firsts { ',' }
tab_firsts.rule_281  = set_firsts { 'TK_VALUETYPE' }
tab_firsts.rule_285  = set_firsts {
  'TK_ONEWAY', 'TK_VOID', 'TK_STRING', 'TK_ID', ':',
  'TK_CHAR', 'TK_BOOLEAN', 'TK_OCTET', 'TK_ANY',
  'TK_OBJECT', 'TK_VALUEBASE', 'TK_LONG', 'TK_FLOAT',
  'TK_DOUBLE', 'TK_SHORT', 'TK_UNSIGNED','TK_TYPEDEF',
  'TK_ENUM', 'TK_NATIVE', 'TK_UNION', 'TK_STRUCT',
  'TK_EXCEPTION', 'TK_READONLY', 'TK_ATTRIBUTE',
  'TK_PUBLIC', 'TK_PRIVATE',
  'TK_FACTORY'
}
tab_firsts.rule_287  = tab_firsts.rule_207
tab_firsts.rule_288  = set_firsts { 'TK_PUBLIC', 'TK_PRIVATE' }
tab_firsts.rule_289  = set_firsts { 'TK_FACTORY' }
tab_firsts.rule_290  = set_firsts { 'TK_PUBLIC' }
tab_firsts.rule_291  = set_firsts { 'TK_PRIVATE' }
tab_firsts.rule_292  = tab_firsts.rule_289
tab_firsts.rule_297  = set_firsts { 'TK_IN' }
tab_firsts.rule_298  = set_firsts { ':', 'TK_SUPPORTS' }
tab_firsts.rule_299  = set_firsts { '{' }
tab_firsts.rule_300  = tab_firsts.rule_27
tab_firsts.rule_302  = tab_firsts.rule_298
tab_firsts.rule_303  = set_firsts { '{' }
tab_firsts.rule_305  = set_firsts { 'TK_MODULE' }
tab_firsts.rule_306  = set_firsts { 'TK_COMPONENT' }
tab_firsts.rule_307  = set_firsts { ':' }
tab_firsts.rule_308  = set_firsts { 'TK_SUPPORTS' }
tab_firsts.rule_309  = set_firsts { '{' }
tab_firsts.rule_316  = set_firsts { 'TK_SUPPORTS' }
tab_firsts.rule_321  = set_firsts { ',' }
tab_firsts.rule_323  = set_firsts { 'TK_PROVIDES', 'TK_USES', 'TK_EMITS', 'TK_PUBLISHES',
                                    'TK_CONSUMES', 'TK_READONLY', 'TK_ATTRIBUTE' }
tab_firsts.rule_325  = set_firsts { 'TK_PROVIDES' }
tab_firsts.rule_326  = set_firsts { 'TK_USES' }
tab_firsts.rule_327  = set_firsts { 'TK_EMITS' }
tab_firsts.rule_328  = set_firsts { 'TK_PUBLISHES' }
tab_firsts.rule_329  = set_firsts { 'TK_CONSUMES' }
tab_firsts.rule_330  = set_firsts { 'TK_READONLY', 'TK_ATTRIBUTE' }
tab_firsts.rule_332  = set_firsts { 'TK_ID', ':' }
tab_firsts.rule_333  = set_firsts { 'TK_OBJECT' }
tab_firsts.rule_339  = set_firsts { 'TK_MULTIPLE' }
tab_firsts.rule_345  = set_firsts { ':' }
tab_firsts.rule_346  = set_firsts { 'TK_SUPPORTS' }
tab_firsts.rule_347  = set_firsts { 'TK_MANAGES' }
tab_firsts.rule_353  = set_firsts { 'TK_PRIMARYKEY' }
tab_firsts.rule_359  = set_firsts {
  'TK_ONEWAY', 'TK_VOID', 'TK_STRING', 'TK_ID', ':',
  'TK_CHAR', 'TK_BOOLEAN', 'TK_OCTET', 'TK_ANY',
  'TK_OBJECT', 'TK_VALUEBASE', 'TK_LONG', 'TK_FLOAT',
  'TK_DOUBLE', 'TK_SHORT', 'TK_UNSIGNED','TK_TYPEDEF',
  'TK_ENUM', 'TK_NATIVE', 'TK_UNION', 'TK_STRUCT',
  'TK_EXCEPTION', 'TK_READONLY', 'TK_ATTRIBUTE',
  'TK_FACTORY', 'TK_FINDER'
}
tab_firsts.rule_361  = tab_firsts.rule_207
tab_firsts.rule_362  = set_firsts { 'TK_FACTORY' }
tab_firsts.rule_363  = set_firsts { 'TK_FINDER' }
tab_firsts.rule_364  = tab_firsts.rule_362
tab_firsts.rule_365  = tab_firsts.rule_363
tab_firsts.rule_366  = tab_firsts.rule_297
tab_firsts.rule_368  = set_firsts { ',' }
tab_firsts.rule_370  = set_firsts { 'TK_RAISES' }

tab_firsts.rule_377  = set_firsts { 'TK_CONTEXT' }

tab_firsts.rule_400  = set_firsts { 'TK_ID' }
tab_firsts.rule_401  = set_firsts { ':' }

tab_follow.rule_32   = set_firsts { 'TK_ID', ';' }
tab_follow.rule_54   = set_firsts { 'TK_ID', '>', ';' }
tab_follow.rule_61   = set_firsts { '>', ',' }
tab_follow.rule_64   = set_firsts { ',', '>' }
tab_follow.rule_69   = set_firsts { '>' }
tab_follow.rule_72   = set_firsts { '>' }
tab_follow.rule_73   = set_firsts { 'TK_ID' }
tab_follow.rule_95   = set_firsts { '|', ']', ')' }
tab_follow.rule_98   = set_firsts { '^', ']', ')' }
tab_follow.rule_102  = set_firsts { '&', ']', ')' }
tab_follow.rule_106  = set_firsts { '>>', '<<', '&', '^', '|', ']', ')' }
tab_follow.rule_111  = set_firsts { '+', '-', '>>', '<<', '&', '^', '|', ']', ')' }
tab_follow.rule_119  = set_firsts { ')' }
tab_follow.rule_139  = set_firsts { '}' }
tab_follow.rule_143  = set_firsts { ';' }
tab_follow.rule_146  = set_firsts { ',', ';' }
tab_follow.rule_147  = set_firsts { '*', '/', '%', '+', '-', '>>', '<<', '&', '^', '|', ']', ')' }
tab_follow.rule_148  = set_firsts { ')' }
tab_follow.rule_154  = set_firsts { ',', ')' }
tab_follow.rule_157  = set_firsts { '}' }
tab_follow.rule_161  = set_firsts {
  'TK_CHAR', 'TK_BOOLEAN', 'TK_OCTET', 'TK_ANY', 'TK_OBJECT',
  'TK_VALUEBASE', 'TK_LONG', 'TK_FLOAT', 'TK_DOUBLE', 'TK_SHORT',
  'TK_UNSIGNED', 'TK_SEQUENCE' , 'TK_STRING', 'TK_FIXED' ,
  'TK_ID', ":", 'TK_STRUCT', 'TK_UNION', 'TK_ENUM',
}
tab_follow.rule_162  = set_firsts { ":" }
tab_follow.rule_167  = set_firsts { "}" }
tab_follow.rule_204  = set_firsts { ',', '{' }
tab_follow.rule_221  = set_firsts { 'TK_ID' }
tab_follow.rule_229  = set_firsts { ',', ')' }
tab_follow.rule_268  = set_firsts { ',', 'TK_SUPPORTS', '{' }
tab_follow.rule_272  = set_firsts { ':', 'TK_ID' }
tab_follow.rule_278  = set_firsts { 'TK_SUPPORTS', '{' }
tab_follow.rule_286  = set_firsts { '}' }
tab_follow.rule_301  = set_firsts { ';' }
tab_follow.rule_304  = set_firsts { ';' }
tab_follow.rule_307  = set_firsts { 'TK_SUPPORTS', '{' }
tab_follow.rule_308  = set_firsts { ',', '{' }
tab_follow.rule_316  = set_firsts { ',', '{' }
tab_follow.rule_316e = set_firsts { '{' }
tab_follow.rule_321  = tab_follow.rule_316
tab_follow.rule_332  = set_firsts { 'TK_ID' }
tab_follow.rule_340  = set_firsts { 'TK_MULTIPLE', 'TK_ID', ':', 'TK_OBJECT' }
tab_follow.rule_341  = set_firsts { 'TK_ID' }
tab_follow.rule_342  = tab_follow.rule_341
tab_follow.rule_343  = tab_follow.rule_342
tab_follow.rule_345  = set_firsts { ',', ':', 'TK_MANAGES' }
tab_follow.rule_347  = set_firsts { 'TK_PRIMARYKEY', '{' }
tab_follow.rule_348  = set_firsts { 'TK_SUPPORTS' }
tab_follow.rule_353  = set_firsts { '{' }
tab_follow.rule_359  = set_firsts { '}' }
tab_follow.rule_367  = set_firsts { ',', ')' }
tab_follow.rule_369  = set_firsts { ')' }
tab_follow.rule_600  = set_firsts { 'TK_STRING_LITERAL' }

local tab_follow_rule_error_msg = {
  [32]  = 'identifier',
  [64]  = "',' or '>'",
  [154] = "',' or ')'",
  [161] = "'char', 'boolean', 'octet', 'any', 'Object',"..
          "'ValueBase', 'long', 'float', 'double', 'short'"..
          "'unsigned', 'sequence', 'string', 'fixed', identifier,"..
          "'struct', 'union', 'enum'",
  [204] = "',', '{'",
  [221] = "identifier",
  [229] = "',', ')'",
  [268] = "',', 'supports' or '{'",
  [307] = "'{'",
  [308] = "',' or '{'",
  [345] = "':', ',' or 'manages'",
  [316] = "',', '{'",
  [332] = "identifier",
  [600] = 'string literal',
}

local token = lex.token

local currentScope
local namespaces
-- It is a stack of roots.
local scopeRoots
local currentScopeName
local CORBAVisible

local tab_identifiers = {}

-- this a list of type declarations
local TAB_TYPEID = {
  ['CONST']     = 'const',
  ['NATIVE']    = 'native',
  ['CHAR']      = 'char',
  ['BOOLEAN']   = 'boolean',
  ['OCTET']     = 'octet',
  ['ANY']       = 'any',
  ['OBJECT']    = 'Object',
  ['VALUEBASE'] = 'valuebase',
  ['STRUCT']    = 'struct',
  ['FLOAT']     = 'float',
  ['SHORT']     = 'short',
  ['FLOAT']     = 'float',
  ['DOUBLE']    = 'double',
  ['USHORT']    = 'ushort',
  ['ULLONG']    = 'ulonglong',
  ['ULONG']     = 'ulong',
  ['LLONG']     = 'longlong',
  ['LDOUBLE']   = 'longdouble',
  ['LONG']      = 'long',
  ['STRING']    = 'string',
  ['FIXED']     = 'fixed',
  ['EXCEPTION'] = 'except',
  ['INTERFACE'] = 'interface',
  ['VOID']      = 'void',
  ['OPERATION'] = 'operation',
  ['TYPEDEF']   = 'typedef',
  ['ENUM']      = 'enum',
  ['SEQUENCE']  = 'sequence',
  ['ATTRIBUTE'] = 'attribute',
  ['MODULE']    = 'module',
  ['UNION']     = 'union',
  ['TYPECODE']  = 'TypeCode',
  ['COMPONENT'] = 'component',
  ['HOME']      = 'home',
  ['FACTORY']   = 'factory',
  ['FINDER']    = 'finder',
  ['VALUEBOX']  = 'valuebox',
  ['VALUETYPE'] = 'valuetype',
  ['EVENTTYPE'] = 'eventtype',
}

local TAB_BASICTYPE = {
  ['NATIVE']    = { _type = TAB_TYPEID['NATIVE'] },
  ['CHAR']      = { _type = TAB_TYPEID['CHAR'] },
  ['BOOLEAN']   = { _type = TAB_TYPEID['BOOLEAN'] },
  ['OCTET']     = { _type = TAB_TYPEID['OCTET'] },
  ['ANY']       = { _type = TAB_TYPEID['ANY'] },
  ['OBJECT']    = { _type = TAB_TYPEID['OBJECT'],
                      repID = 'IDL:omg.org/CORBA/Object:1.0' },
  ['VALUEBASE'] = { _type = TAB_TYPEID['VALUEBASE'] },
  ['FLOAT']     = { _type = TAB_TYPEID['FLOAT'] },
  ['SHORT']     = { _type = TAB_TYPEID['SHORT'] },
  ['FLOAT']     = { _type = TAB_TYPEID['FLOAT'] } ,
  ['DOUBLE']    = { _type = TAB_TYPEID['DOUBLE'] },
  ['USHORT']    = { _type = TAB_TYPEID['USHORT'] },
  ['ULLONG']    = { _type = TAB_TYPEID['ULLONG'] },
  ['ULONG']     = { _type = TAB_TYPEID['ULONG'] },
  ['LLONG']     = { _type = TAB_TYPEID['LLONG'] },
  ['LDOUBLE']   = { _type = TAB_TYPEID['LDOUBLE'] },
  ['LONG']      = { _type = TAB_TYPEID['LONG'] },
  ['FIXED']     = { _type = TAB_TYPEID['FIXED'] },
  ['VOID']      = { _type = TAB_TYPEID['VOID'] },
  ['STRING']    = { _type = TAB_TYPEID['STRING'] },
}

local TAB_IMPLICITTYPE = {
  ['TYPECODE']  = { _type = TAB_TYPEID['TYPECODE'],
                      repID = 'IDL:omg.org/CORBA/TypeCode:1.0' },
}

local tab_legal_type = {
  [TAB_TYPEID.TYPEDEF] = true,
  [TAB_TYPEID.STRUCT] = true,
  [TAB_TYPEID.ENUM] = true,
  [TAB_TYPEID.INTERFACE] = true,
  [TAB_TYPEID.NATIVE] = true,
  [TAB_TYPEID.UNION] = true,
  [TAB_TYPEID.CHAR] = true,
  [TAB_TYPEID.BOOLEAN] = true,
  [TAB_TYPEID.OCTET] = true,
  [TAB_TYPEID.ANY] = true,
  [TAB_TYPEID.OBJECT] = true,
  [TAB_TYPEID.VALUEBASE] = true,
  [TAB_TYPEID.FLOAT] = true,
  [TAB_TYPEID.DOUBLE] = true,
  [TAB_TYPEID.SHORT] = true,
  [TAB_TYPEID.USHORT] = true,
  [TAB_TYPEID.ULLONG] = true,
  [TAB_TYPEID.ULONG] = true,
  [TAB_TYPEID.LLONG] = true,
  [TAB_TYPEID.LDOUBLE] = true,
  [TAB_TYPEID.LONG] = true,
  [TAB_TYPEID.FIXED] = true,
  [TAB_TYPEID.VOID] = true,
  [TAB_TYPEID.TYPECODE] = true,
  [TAB_TYPEID.SEQUENCE] = true,
  [TAB_TYPEID.STRING] = true,
}

local tab_accept_definition = {
  [TAB_TYPEID.STRUCT] = true,
  [TAB_TYPEID.EXCEPTION] = true,
  [TAB_TYPEID.INTERFACE] = true,
  [TAB_TYPEID.MODULE] = true,
  [TAB_TYPEID.COMPONENT] = true,
  [TAB_TYPEID.HOME] = true,
  [TAB_TYPEID.VALUETYPE] = true,
  [TAB_TYPEID.EVENTTYPE] = true,
}

local tab_define_scope = {
  [TAB_TYPEID.INTERFACE] = true,
  [TAB_TYPEID.EXCEPTION] = true,
  [TAB_TYPEID.OPERATION] = true,
  [TAB_TYPEID.FACTORY] = true,
  [TAB_TYPEID.STRUCT] = true,
  [TAB_TYPEID.UNION] = true,
  [TAB_TYPEID.MODULE] = true,
  [TAB_TYPEID.COMPONENT] = true,
  [TAB_TYPEID.VALUETYPE] = true,
}

local tab_is_contained = {
  [TAB_TYPEID.ATTRIBUTE] = true,
  [TAB_TYPEID.TYPEDEF] = true,
  [TAB_TYPEID.INTERFACE] = true,
  [TAB_TYPEID.OPERATION] = true,
  [TAB_TYPEID.CONST] = true,

  [TAB_TYPEID.STRUCT] = true,
  [TAB_TYPEID.EXCEPTION] = true,
  [TAB_TYPEID.MODULE] = true,
  [TAB_TYPEID.ENUM] = true,
  [TAB_TYPEID.UNION] = true,
  [TAB_TYPEID.COMPONENT] = true,
  [TAB_TYPEID.HOME] = true,
  [TAB_TYPEID.VALUETYPE] = true,
  [TAB_TYPEID.VALUEBOX] = true,
  [TAB_TYPEID.EVENTTYPE] = true,
  [TAB_TYPEID.TYPECODE] = true,
}

local TAB_VALUEEXPECTED = {
  [lex.tab_tokens.TK_ID]              = "<identifier>",
  [lex.tab_tokens.TK_ABSTRACT]        = "abstract",
  [lex.tab_tokens.TK_ANY]             = TAB_TYPEID.ANY,
  [lex.tab_tokens.TK_ATTRIBUTE]       = TAB_TYPEID.ATTRIBUTE,
  [lex.tab_tokens.TK_BOOLEAN]         = TAB_TYPEID.BOOLEAN,
  [lex.tab_tokens.TK_CASE]            = "case",
  [lex.tab_tokens.TK_CHAR]            = TAB_TYPEID.CHAR,
  [lex.tab_tokens.TK_COMPONENT]       = TAB_TYPEID.COMPONENT,
  [lex.tab_tokens.TK_CONST]           = TAB_TYPEID.CONST,
  [lex.tab_tokens.TK_CONSUMES]        = "consumes",
  [lex.tab_tokens.TK_CONTEXT]         = "context",
  [lex.tab_tokens.TK_CUSTOM]          = "custom",
  [lex.tab_tokens.TK_DEFAULT]         = "default",
  [lex.tab_tokens.TK_DOUBLE]          = TAB_TYPEID.DOUBLEF,
  [lex.tab_tokens.TK_EXCEPTION]       = TAB_TYPEID.EXCEPTION,
  [lex.tab_tokens.TK_EMITS]           = "emits",
  [lex.tab_tokens.TK_ENUM]            = TAB_TYPEID.ENUM,
  [lex.tab_tokens.TK_EVENTTYPE]       = TAB_TYPEID.EVENTTYPE,
  [lex.tab_tokens.TK_FACTORY]         = TAB_TYPEID.FACTORY,
  [lex.tab_tokens.TK_FALSE]           = "FALSE",
  [lex.tab_tokens.TK_FINDER]          = TAB_TYPEID.FINDER,
  [lex.tab_tokens.TK_FIXED]           = TAB_TYPEID.FIXED,
  [lex.tab_tokens.TK_FLOAT]           = TAB_TYPEID.FLOAT,
  [lex.tab_tokens.TK_GETRAISES]       = "getraises",
  [lex.tab_tokens.TK_HOME]            = TAB_TYPEID.HOME,
  [lex.tab_tokens.TK_IMPORT]          = "import",
  [lex.tab_tokens.TK_IN]              = "in",
  [lex.tab_tokens.TK_INOUT]           = "inout",
  [lex.tab_tokens.TK_INTERFACE]       = TAB_TYPEID.INTERFACE,
  [lex.tab_tokens.TK_LOCAL]           = "local",
  [lex.tab_tokens.TK_LONG]            = TAB_TYPEID.LONG,
  [lex.tab_tokens.TK_MODULE]          = TAB_TYPEID.MODULE,
  [lex.tab_tokens.TK_MULTIPLE]        = "multiple",
  [lex.tab_tokens.TK_NATIVE]          = TAB_TYPEID.NATIVE,
  [lex.tab_tokens.TK_OBJECT]          = TAB_TYPEID.OBJECT,
  [lex.tab_tokens.TK_OCTET]           = TAB_TYPEID.OCTET,
  [lex.tab_tokens.TK_ONEWAY]          = "oneway",
  [lex.tab_tokens.TK_OUT]             = "out",
  [lex.tab_tokens.TK_PRIMARYKEY]      = "primarykey",
  [lex.tab_tokens.TK_PRIVATE]         = "private",
  [lex.tab_tokens.TK_PROVIDES]        = "provides",
  [lex.tab_tokens.TK_PUBLIC]          = "public",
  [lex.tab_tokens.TK_PUBLISHES]       = "publishes",
  [lex.tab_tokens.TK_RAISES]          = "raises",
  [lex.tab_tokens.TK_READONLY]        = "readonly",
  [lex.tab_tokens.TK_SETRAISES]       = "setraises",
  [lex.tab_tokens.TK_SEQUENCE]        = "sequence",
  [lex.tab_tokens.TK_SHORT]           = TAB_TYPEID.SHORT,
  [lex.tab_tokens.TK_STRING]          = TAB_TYPEID.STRING,
  [lex.tab_tokens.TK_STRUCT]          = TAB_TYPEID.STRUCT,
  [lex.tab_tokens.TK_SUPPORTS]        = "supports",
  [lex.tab_tokens.TK_SWITCH]          = "switch",
  [lex.tab_tokens.TK_TRUE]            = "TRUE",
  [lex.tab_tokens.TK_TRUNCATABLE]     = "truncatable",
  [lex.tab_tokens.TK_TYPEDEF]         = TAB_TYPEID.TYPEDEF,
  [lex.tab_tokens.TK_TYPEID]          = "typeid",
  [lex.tab_tokens.TK_TYPEPREFIX]      = "typeprefix",
  [lex.tab_tokens.TK_UNSIGNED]        = "unsigned",
  [lex.tab_tokens.TK_UNION]           = TAB_TYPEID.UNION,
  [lex.tab_tokens.TK_USES]            = "uses",
  [lex.tab_tokens.TK_VALUEBASE]       = TAB_TYPEID.VALUEBASE,
  [lex.tab_tokens.TK_VALUETYPE]       = TAB_TYPEID.VALUETYPE,
  [lex.tab_tokens.TK_VOID]            = TAB_TYPEID.VOID,
  [lex.tab_tokens.TK_WCHAR]           = "wchar",
  [lex.tab_tokens.TK_WSTRING]         = "wstring",
  [lex.tab_tokens.TK_INTEGER_LITERAL] = "<integer literal>",
  [lex.tab_tokens.TK_FLOAT_LITERAL]   = "<float literal>",
  [lex.tab_tokens.TK_CHAR_LITERAL]    = "<char literal>",
  [lex.tab_tokens.TK_WCHAR_LITERAL]   = "<wchar literal>",
  [lex.tab_tokens.TK_STRING_LITERAL]  = "<string literal>",
  [lex.tab_tokens.TK_WSTRING_LITERAL] = "<wstring literal>",
  [lex.tab_tokens.TK_FIXED_LITERAL]   = "<fixed literal>",
  [lex.tab_tokens.TK_PRAGMA_PREFIX]   = "<pragma prefix>",
  [lex.tab_tokens.TK_PRAGMA_ID]       = "<pragma id>",
  [lex.tab_tokens.TK_MANAGES]         = "manages",
}

local rules = {}


---
-- Error reporting
---------------------------------------------------------------------------------------------------
local ERRMSG_DECLARED       = "'%s' has already been declared"
local ERRMSG_PARAMDECLARED  = "parameter '%s' has already been declared"
local ERRMSG_RAISESDECLARED = "raise '%s' has already been declared"
local ERRMSG_OPDECLARED     = "operation '%s' has already been declared"
local ERRMSG_REDEFINITION   = "redefinition of '%s'"
local ERRMSG_NOTTYPE        = "%s is not a legal type"
local ERRMSG_UNDECLARED     = "%s is an undeclared type"
local ERRMSG_FORWARD        = "There is a forward reference to %s, but it is not defined"

local tab_ERRORMSG ={
  [01] = "definition ('typedef', 'enum', 'native', 'union', 'struct', "..
          "'const', 'exception', 'abstract', 'local', "..
          "'interface', 'custom', 'valuetype', 'eventtype', "..
          "'module', 'typeid', 'typeprefix', 'component' or 'home')",
  [02] = "type declaration ('typedef', 'struct', 'union', 'enum' or 'native')",
  [03] = "type specification ('char', 'boolean', 'octet', 'any', 'Object', "..
          "'ValueBase', 'long', 'float', 'double', 'short', 'unsigned', 'sequence', "..
          "'string', 'fixed', identifier, 'struct', 'union', 'enum')",
  [04] = "simple type specification (base type, template type or a scoped name)",
  [05] = "base type specification ('char', 'boolean', 'octet', 'any', 'Object', "..
          "'ValueBase', 'long', 'float', 'double', 'short', 'unsigned')",
  [06] = "'float', 'double', 'short', 'unsigned' or 'long'",
  [07] = "'float' or 'double'",
  [08] = "'short' or 'unsigned'",
  [09] = "'long' or 'short'",
--follows!?
  [10] = "'long'",
  [11] = "',' or ';'",
  [12] = "'[', ',' or ';'",
  [13] = "'-', '+', '~', '(', identifier, ':', <integer literal>,"..
          "<string literal>, <char literal>, <fixed literal>,"..
          "<float literal>, 'TRUE' or 'FALSE'",
  [14] = "'-', '+', '~'",
  [15] = "'(', identifier, ':', <integer literal>,"..
          "<string literal>, <char literal>, <fixed literal>,"..
          "<float literal>, 'TK_TRUE', 'TK_FALSE'",
  [16] = "<integer literal>, <string literal>, <char literal>,"..
          "<fixed literal>, <float literal>",
  [17] = "'TK_TRUE', 'TK_FALSE'",
  [18] = "'*', '/', '%', '+', '-', ']', ')', '>>', '<<', '&', '^', '|'",
  [19] = "'+', '-', '>>', '<<'",
  [20] = "'>>', '<<', '&'",
  [21] = "'&', '^'",
  [22] = "'^', '|'",
  [23] = "'|'",
  [24] = "you must entry with a positive integer",
  [25] = "you must entry with a integer",
  [26] = "'<' or identifier",
  [27] = "constructed type specification ('struct', 'union' or 'enum')",
  [28] = "type specification or '}'",
  [29] = "'short', 'unsigned', 'char', 'boolean', 'enum', identifier, '::'",
  [30] = "'case', 'default'",
  [31] = "'case', 'default' or type specification",
  [32] = "'case', 'default' or '}'",
}

local function sinError(valueExpected)
  error(string.format("%s(line %i): %s expected, encountered '%s'." ,
      lex.srcfilename, lex.line, valueExpected, lex.tokenvalue), 2)
end

local function semanticError(error_msg)
  local scope = currentScope.absolute_name
  if (scope == '') then
    scope = 'GLOBAL'
  end
  error(string.format("%s(line %i):Scope:'%s': %s.", lex.srcfilename,
      lex.line, scope, error_msg), 2)
end
---------------------------------------------------------------------------------------------------


---
-- Auxiliar functions
---------------------------------------------------------------------------------------------------
local function getID()
  return lex.tokenvalue_previous  
end

local function registerID(id)
  if (string.sub(id, 1, 2) == "::") then
   id = string.sub(id, 3)
  end
  tab_identifiers[string.upper(currentScope.absolute_name.."::"..id)] = true;
end

local function gotoFatherScope()
  if (scopeRoots[#scopeRoots].scope == currentScope.absolute_name) then
    table.remove(scopeRoots)
  end
  local currentRoot = scopeRoots[#scopeRoots].root
  if (currentScope._type == TAB_TYPEID.MODULE) then
    currentRoot = string.gsub(currentRoot, "::[^:]+$", "")
    scopeRoots[#scopeRoots].root = currentRoot
  elseif (currentScope._type == TAB_TYPEID.INTERFACE) or
         (currentScope._type == TAB_TYPEID.STRUCT) or
         (currentScope._type == TAB_TYPEID.UNION) or
         (currentScope._type == TAB_TYPEID.EXCEPTION)
  then
    currentScopeName = string.gsub(currentScopeName, "::[^:]+$", "")
  end
  currentScope = namespaces[currentScope.absolute_name].father_scope
end

local function getAbsolutename(scope, name)
  return scope.absolute_name..'::'..name
end

local function dclName(name, target, value)
  local absolutename = getAbsolutename(currentScope, name)
  if namespaces[absolutename] then
    semanticError(string.format(ERRMSG_DECLARED, name))
  else
    if tab_identifiers[string.upper(absolutename)] then
      semanticError("collide")
    end
    namespaces[absolutename] = {namespace = name}
    if value then
      value.name = name
      table.insert(target, value)
    else
      table.insert(target, name)
    end
  end
end

local recognize

local function getToken()
  token = lex.lexer(idl)

  for _, linemark in ipairs(lex.tab_linemarks) do
    if linemark['1'] then
      table.insert(scopeRoots, {root = '', scope = currentScope.absolute_name})
    elseif linemark['2'] then
      table.remove(scopeRoots)
    end
  end
  lex.tab_linemarks = {}

-- The ID Pragma
-- #pragma ID <name> "<id>"
  if (token == lex.tab_tokens.TK_PRAGMA_ID) then
    token = lex.lexer(idl)
    local definition = rules.scoped_name(600)
    local repid = lex.tokenvalue
    recognize(lex.tab_tokens.TK_STRING_LITERAL)
    local absolutename = definition.absolute_name
    if namespaces[absolutename].pragmaID then
      if (definition.repID ~= repid) then
        semanticError("repository ID ever defined")
      end
    else
      namespaces[absolutename].pragmaID = true
      definition.repID = repid
    end
-- The Prefix Pragma
-- #pragma prefix "<string>"
  elseif (token == lex.tab_tokens.TK_PRAGMA_PREFIX) then
    token = lex.lexer(idl)
    local prefix = lex.tokenvalue
    if (scopeRoots[#scopeRoots].scope == currentScope.absolute_name) then
      table.remove(scopeRoots)
    end
    table.insert(scopeRoots, {root = prefix, scope = currentScope.absolute_name})
    recognize(lex.tab_tokens.TK_STRING_LITERAL)
  end
  return token
end

function recognize(tokenExpected)
  if (tokenExpected == token) then
    token = getToken()
  else
    local valueExpected = TAB_VALUEEXPECTED[tokenExpected]
    if not valueExpected then
      valueExpected = "'"..tokenExpected.."'"
    end
    sinError(valueExpected)
  end
end

local function updateGlobalName(type, name)
  local localName = ''
  local currentRoot = scopeRoots[#scopeRoots].root
-- Whenever a module is encountered, the string "::" and the <name> are appended
-- to the name of the current root.
  if (type == TAB_TYPEID.MODULE) then
    currentRoot = currentRoot..'::'..name
-- Whenever a interface, struct, union or exception is encountered,
-- the string "::" and the <name> are appended to the name of the current scope.
  elseif (
          (type == TAB_TYPEID.INTERFACE) or
          (type == TAB_TYPEID.STRUCT) or
          (type == TAB_TYPEID.UNION) or
          (type == TAB_TYPEID.EXCEPTION)
         )
  then
    currentScopeName = currentScopeName..'::'..name
  else
    localName = '::'..name
  end
  scopeRoots[#scopeRoots].root = currentRoot
  return currentRoot, currentScopeName, localName
end

-- Define an OMG IDL definition.
local function define(name, type, namespace)
  local absolutename = getAbsolutename(currentScope, name)
  local definitions

-- Esta definição já foi declarada anteriormente?
  if (namespaces[absolutename]) then
  -- Um módulo está sendo reaberto?
    if (
        (namespaces[absolutename].namespace._type == TAB_TYPEID.MODULE)
          and
        (type == TAB_TYPEID.MODULE)
       )
    then
      namespace = namespaces[absolutename].namespace
      currentScope = namespace
      updateGlobalName(type, name)
      return nil, namespace
    else
      semanticError(string.format(ERRMSG_REDEFINITION, name))
    end
  end

-- A definição já foi declarada como forward?
  if forwardDeclarations[absolutename] then
    namespace = forwardDeclarations[absolutename]
    forwardDeclarations[absolutename] = nil
  end

  if (not definitions and tab_accept_definition[type]) then
    definitions = {}
  end

  local root, scope, localName = updateGlobalName(type, name)
  repID = root..scope..localName
  repID = string.gsub(string.gsub(repID, "^::", ""), "::", "/")

  if (not namespace) then
    namespace = {}
  end

  namespace.name = name
  namespace._type = type
  namespace.absolute_name = absolutename
  namespace.repID = "IDL:"..repID..":"..lex.PRAGMA_VERSION
  namespace.definitions = definitions

  if (tab_is_contained[type] and currentScope ~= output) then
    table.insert(currentScope.definitions, namespace)
  elseif (type == TAB_TYPEID.FACTORY) then
    currentScope.initializers = currentScope.initializers or {}
    table.insert(currentScope.initializers, namespace)
  else
    table.insert(currentScope, namespace)
  end

  if (tab_define_scope[type]) then
    namespaces[absolutename] = {
                                 father_scope = currentScope,
                                 namespace = namespace,
                               }
    currentScope = namespace
  else
    namespaces[absolutename] = {namespace = namespace}
  end
  return true, namespace
end

-- This is an auxiliar function for getDefinition().
local function getTabDefinition(name)
  local namespace
  if namespaces[name] then
    namespace = namespaces[name].namespace
  end
  return namespace or forwardDeclarations[name]
end

local function getDefinition(name, baseScope)
  local scope = currentScope
-- Busca uma definição em um escopo previamente fornecido.
  if baseScope then
    local definition = getTabDefinition(baseScope..'::'..name)
    if (definition) then
      return definition
    end
  else
    while true do
      local absolutename = getAbsolutename(scope, name)
      local definition = getTabDefinition(absolutename)
      if definition then
        return definition
      end
      if (scope._type == TAB_TYPEID.INTERFACE) then
      -- Busca a definição nas interfaces de base.
        for _, base in ipairs(scope) do
          absolutename = getAbsolutename(namespaces[base.absolute_name].namespace, name)
          local definition = getTabDefinition(absolutename)
          if definition then
            return definition
          end
        end
      end
    -- Se a definição não foi encontrada no escopo atual, então a busca continua
    -- no escopo *pai*.
      if (scope ~= output) then
        scope = namespaces[scope.absolute_name].father_scope
      else
        if (currentScope._type == TAB_TYPEID.UNION) then
          if (currentScope.switch._type == TAB_TYPEID.ENUM) then
            return namespaces[getAbsolutename(currentScope.switch, scope)].namespace
          end
        end
        break
      end
    end
  end
  semanticError(string.format(ERRMSG_UNDECLARED, name))
end

-- Define uma declaração forward.
local function dclForward(name, type)
  local absolute_name = getAbsolutename(currentScope, name)
  local definition = namespaces[absolute_name] or
                     forwardDeclarations[absolute_name]
  if not definition then
    definition = {name = name, _type = type, absolute_name = absolute_name}
    forwardDeclarations[absolute_name] = definition
  end
  return definition
end
---------------------------------------------------------------------------------------------------


---
-- GRAMMAR RULES
--------------------------------------------------------------------------

rules.specification = function ()
--  import_l()
  if (callbacks.start) then
    callbacks.start()
  end
  rules.definition_l()
-- Is there any forward reference without definition?
  for definition, _ in pairs(forwardDeclarations) do
    semanticError(string.format(ERRMSG_FORWARD, definition))
  end
  if (callbacks.finish) then
    callbacks.finish()
  end
end

rules.definition_l = function ()
  if (tab_firsts.rule_11[token]) then
    rules.definition()
    rules.definition_l_r()
  else
    sinError(tab_ERRORMSG[01])
  end
end

rules.definition_l_r = function ()
  if (tab_firsts.rule_12[token]) then
    rules.definition()
    rules.definition_l_r()
  elseif (not token) then
    --empty
  else
    sinError(tab_ERRORMSG[01])
  end
end

rules.definition = function ()
  if (tab_firsts.rule_14[token]) then
    rules.type_dcl()
  elseif (tab_firsts.rule_15[token]) then
    rules.const_dcl()
  elseif (tab_firsts.rule_16[token]) then
    rules.except_dcl()
  elseif (tab_firsts.rule_17[token]) then
    rules.inter_value_event()
  elseif (tab_firsts.rule_18[token]) then
    rules.module()
  elseif (tab_firsts.rule_19[token]) then
    rules.type_id_dcl()
  elseif (tab_firsts.rule_20[token]) then
    rules.type_prefix_dcl()
  elseif (tab_firsts.rule_21[token]) then
    rules.component()
  elseif (tab_firsts.rule_22[token]) then
    rules.home_dcl()
  end
  recognize(";")
end

rules.const_dcl = function ()
  if (tab_firsts.rule_174[token]) then
    recognize(lex.tab_tokens.TK_CONST)
    local type = rules.const_type()
    recognize(lex.tab_tokens.TK_ID)
    local name = getID()
    recognize("=")
    local value = rules.positive_int_const(143)
    local const = {type = type, value = value}
    define(name, TAB_TYPEID.CONST, const)
    if (callbacks.const) then
      callbacks.const(const)
    end
  end
end

rules.const_type = function ()
  if (tab_firsts.rule_175[token]) then
    return rules.float_type_or_int_type()
  elseif (tab_firsts.rule_176[token]) then
    recognize(lex.tab_tokens.TK_CHAR)
    return TAB_BASICTYPE.CHAR
  elseif (tab_firsts.rule_177[token]) then
    recognize(lex.tab_tokens.TK_BOOLEAN)
    return TAB_BASICTYPE.BOOLEAN
  elseif (tab_firsts.rule_178[token]) then
    recognize(lex.tab_tokens.TK_STRING)
    return TAB_BASICTYPE.STRING
  elseif (tab_firsts.rule_179[token]) then
    return rules.scoped_name(32)
  elseif (tab_firsts.rule_180[token]) then
    recognize(lex.tab_tokens.TK_OCTET)
    return TAB_BASICTYPE.OCTET
  elseif (tab_firsts.rule_181[token]) then
    recognize(lex.tab_tokens.TK_FIXED)
    return TAB_BASICTYPE.FIXED
  end
end

rules.type_dcl = function ()
  if (tab_firsts.rule_23[token]) then
    recognize(lex.tab_tokens.TK_TYPEDEF)
    rules.type_declarator()
  elseif (tab_firsts.rule_24[token]) then
    rules.enum_type()
  elseif (tab_firsts.rule_25[token]) then
    recognize(lex.tab_tokens.TK_NATIVE)
    recognize(lex.tab_tokens.TK_ID)
    define(getID(), TAB_TYPEID.NATIVE)
  elseif (tab_firsts.rule_26[token]) then
    rules.union_or_struct()
  else
    sinError(tab_ERRORMSG[02])
  end
end

rules.type_declarator = function ()
  local type = rules.type_spec()
  if (not tab_legal_type[type._type]) then
    semanticError(string.format(ERRMSG_NOTTYPE, type._type))
  end
  rules.type_dcl_name_l(type)
end

rules.type_spec = function (numrule)
  if (tab_firsts.rule_28[token]) then
    return rules.simple_type_spec(numrule)
  elseif (tab_firsts.rule_29[token]) then
    return rules.constr_type_spec()
  else
    sinError(tab_ERRORMSG[03])
  end
end

rules.simple_type_spec = function (numrule)
  if (tab_firsts.rule_30[token]) then
    return rules.base_type_spec()
  elseif (tab_firsts.rule_31[token]) then
    return rules.template_type_spec()
  elseif (tab_firsts.rule_32[token]) then
    tab = rules.scoped_name(numrule or 32)
    return tab
  else
    sinError(tab_ERRORMSG[04])
  end
end

rules.base_type_spec = function ()
  if (tab_firsts.rule_36[token]) then
    return rules.float_type_or_int_type()
  elseif (tab_firsts.rule_37[token]) then
    recognize(lex.tab_tokens.TK_CHAR)
    return TAB_BASICTYPE.CHAR
  elseif (tab_firsts.rule_38[token]) then
    recognize(lex.tab_tokens.TK_BOOLEAN)
    return TAB_BASICTYPE.BOOLEAN
  elseif (tab_firsts.rule_39[token]) then
    recognize(lex.tab_tokens.TK_OCTET)
    return TAB_BASICTYPE.OCTET
  elseif (tab_firsts.rule_40[token]) then
    recognize(lex.tab_tokens.TK_ANY)
    return TAB_BASICTYPE.ANY
  elseif (tab_firsts.rule_41[token]) then
    recognize(lex.tab_tokens.TK_OBJECT)
    return TAB_BASICTYPE.OBJECT
  elseif (tab_firsts.rule_42[token]) then
    recognize(lex.tab_tokens.TK_VALUEBASE)
    return TAB_BASICTYPE.VALUEBASE
--  else
--    sinError(tab_ERRORMSG[05])
  end
end

rules.float_type_or_int_type = function ()
  if (tab_firsts.rule_43[token]) then
    return rules.floating_pt_type()
  elseif (tab_firsts.rule_44[token]) then
    return rules.integer_type(54)
  elseif (tab_firsts.rule_45[token]) then
    recognize(lex.tab_tokens.TK_LONG)
    return rules.long_or_double()
  else
    sinError(tab_ERRORMSG[06])
  end
end

rules.floating_pt_type = function ()
  if (tab_firsts.rule_46[token]) then
    recognize(lex.tab_tokens.TK_FLOAT)
    return TAB_BASICTYPE.FLOAT
  elseif (tab_firsts.rule_47[token]) then
    recognize(lex.tab_tokens.TK_DOUBLE)
    return TAB_BASICTYPE.DOUBLE
--  else
--    sinError(tab_ERRORMSG[07])
  end
end

rules.integer_type = function (numrule)
  if (tab_firsts.rule_48[token]) then
    recognize(lex.tab_tokens.TK_SHORT)
    return TAB_BASICTYPE.SHORT
  elseif (tab_firsts.rule_49[token]) then
    return rules.unsigned_int(numrule)
--  else
--    sinError(tab_ERRORMSG[08])
  end
end

rules.unsigned_int = function (numrule)
  recognize(lex.tab_tokens.TK_UNSIGNED)
  return rules.unsigned_int_tail(numrule)
end

rules.unsigned_int_tail = function (numrule)
  if (tab_firsts.rule_51[token]) then
    recognize(lex.tab_tokens.TK_LONG)
    return rules.ulong_e(numrule)
  elseif (tab_firsts.rule_52[token]) then
    recognize(lex.tab_tokens.TK_SHORT)
    return TAB_BASICTYPE.USHORT
  else
    sinError(tab_ERRORMSG[09])
  end
end

rules.long_e = function (numrule)
  if (tab_firsts.rule_53[token]) then
    recognize(lex.tab_tokens.TK_LONG)
    return TAB_BASICTYPE.LLONG
  elseif (tab_follow['rule_'..numrule][token]) then
    return TAB_BASICTYPE.LONG
    --empty
  else
    sinError(tab_ERRORMSG[10])
  end
end

rules.ulong_e = function (numrule)
  if (tab_firsts.rule_53[token]) then
    recognize(lex.tab_tokens.TK_LONG)
    return TAB_BASICTYPE.ULLONG
  elseif (tab_follow['rule_'..numrule][token]) then
    return TAB_BASICTYPE.ULONG
    --empty
  else
    sinError(tab_ERRORMSG[10])
  end
end

rules.type_dcl_name_l = function (type)
  rules.type_dcl_name(type)
  rules.type_dcl_name_l_r(type)
end

rules.type_dcl_name_l_r = function (type)
  if (tab_firsts.rule_142[token]) then
    recognize(",")
    rules.type_dcl_name(type)
    rules.type_dcl_name_l_r(type)
  elseif (tab_follow.rule_143 [token]) then
    --empty
  else
    sinError(tab_ERRORMSG[11])
  end
end

rules.type_dcl_name = function (type)
  recognize(lex.tab_tokens.TK_ID)
  local name = getID()
  local typedef = {original_type = rules.fixed_array_size_l(type)}
  define(name, TAB_TYPEID.TYPEDEF, typedef)
  if (callbacks.typedef) then
    callbacks.typedef(typedef)
  end
end

-- without revision
rules.fixed_array_size_l = function (tab_type_spec)
  if (tab_firsts.rule_145[token]) then
    local array =  {
      length = rules.fixed_array_size(tab_type_spec),
      elementtype = rules.fixed_array_size_l(tab_type_spec),
      _type = 'array'
    }
    if callbacks.array then
      callbacks.array(array)
    end
    return array
  elseif (tab_follow.rule_146[token]) then
    --empty
    return tab_type_spec
  else
    sinError(tab_ERRORMSG[12])
  end
end

rules.fixed_array_size = function (tab_type_spec)
  recognize("[")
  local const = rules.positive_int_const(147)
  recognize("]")
  return const
end

-- without revision
--without revision
--without bitwise logical operations
rules.positive_int_const = function (numrule)
  if tab_firsts.rule_75[token] then
    local const1 = rules.xor_expr(numrule)
    rules.or_expr_l(numrule)
    if type(const1) == "string" and string.find(const1, '[%d]') then
     const1 = tonumber(const1)
     if const1 < 0 then
        semanticError(tab_ERRORMSG[24])
      end
    end
    return const1
  else
    sinError(tab_ERRORMSG[13])
  end
end


rules.xor_expr = function (numrule)
  if tab_firsts.rule_93[token] then
    local exp1 = rules.and_expr(numrule)
    rules.xor_expr_l(numrule)
    return exp1
--  else
--    sinError(tab_ERRORMSG[13])
  end
end


rules.and_expr = function (numrule)
  if tab_firsts.rule_96[token] then
    local const1 = rules.shift_expr(numrule)
    return rules.and_expr_l(const1, numrule)
--  else
--    sinError(tab_ERRORMSG[13])
  end
end


rules.shift_expr = function (numrule)
  if tab_firsts.rule_99[token] then
    local const1 = rules.add_expr(numrule)
    return rules.shift_expr_l(const1, numrule)
--  else
--    sinError(tab_ERRORMSG[13])
  end
end


rules.add_expr = function (numrule)
  if tab_firsts.rule_103[token] then
    local const1 = rules.mult_expr(numrule)
    return rules.add_expr_l(const1, numrule)
--  else
--    sinError(tab_ERRORMSG[13])
  end
end


rules.mult_expr = function (numrule)
  if tab_firsts.rule_107[token] then
    local const = rules.unary_expr()
--[[   if not is_num(const) then
      semanticError(tab_ERRORMSG[25])
    end
]]
    const = rules.mult_expr_l(const, numrule)
    return const
--  else
--    sinError(tab_ERRORMSG[13])
  end
end


--semantic of '~' operator ???!!
rules.unary_expr = function ()
  if tab_firsts.rule_112[token] then
    local op = rules.unary_operator()
    local exp = rules.primary_expr()
    if tonumber(exp) then
      if op == '-' then
        exp = tonumber('-'..exp)
      elseif op == '+' then
        exp = tonumber('+'..exp)
      end
    end
    return exp
  elseif tab_firsts.rule_113[token] then
    return rules.primary_expr()
--  else
--    sinError(tab_ERRORMSG[13])
  end
end

rules.unary_operator = function ()
  if tab_firsts.rule_114[token] then
    recognize("-")
    return '-'
  elseif tab_firsts.rule_115[token] then
    recognize("+")
    return '+'
  elseif tab_firsts.rule_116[token] then
    recognize("~")
    return '~'
--  else
--    sinError(tab_ERRORMSG[14])
  end
end


rules.primary_expr = function ()
  if tab_firsts.rule_117[token] then
    local value = rules.case_label_aux()
    if type(value) == 'table' then
       sinError("The <scoped_name> in the <const_type> production must be a previously \
                  defined name of an <integer_type>, <char_type>, <wide_char_type>, \
                  <boolean_type>, <floating_pt_type>, \
                  <string_type>, <wide_string_type>, <octet_type>, or <enum_type> constant.")
    end
    return value
  elseif tab_firsts.rule_118[token] then
    local value = rules.literal()
    if (currentScope._type == TAB_TYPEID.UNION) then
      recognize(":")
    end
    return value
  elseif tab_firsts.rule_119[token] then
    recognize("(")
    local const = rules.positive_int_const(119)
    recognize(")")
    return const
  else
    sinError(tab_ERRORMSG[15])
  end
end

rules.literal = function ()
  if tab_firsts.rule_120[token] then
    recognize(lex.tab_tokens.TK_INTEGER_LITERAL)
    return getID()
  elseif tab_firsts.rule_121[token] then
    recognize(lex.tab_tokens.TK_STRING_LITERAL)
    return getID()
  elseif tab_firsts.rule_122[token] then
    recognize(lex.tab_tokens.TK_CHAR_LITERAL)
    return getID()
  elseif tab_firsts.rule_123[token] then
    recognize(lex.tab_tokens.TK_FIXED_LITERAL)
    return getID()
  elseif tab_firsts.rule_124[token] then
    recognize(lex.tab_tokens.TK_FLOAT_LITERAL)
    return getID()
  elseif tab_firsts.rule_125[token] then
    return rules.boolean_literal()
--  else
--    sinError(tab_ERRORMSG[16])
  end
end


rules.boolean_literal = function ()
  if tab_firsts.rule_126[token] then
    recognize(lex.tab_tokens.TK_TRUE)
    return true
  elseif tab_firsts.rule_127[token] then
    recognize(lex.tab_tokens.TK_FALSE)
    return false
--  else
--    sinError(tab_ERRORMSG[17])
  end
end


rules.mult_expr_l = function (const1, numrule)
  if tab_firsts.rule_108[token] then
    recognize("*")
    local const2 = rules.unary_expr()
    if not tonumber(const2) then
      semanticError(tab_ERRORMSG[25])
    end
    local const = const1 * const2
    return rules.mult_expr_l(const, numrule)
  elseif tab_firsts.rule_109[token] then
    recognize("/")
    local const2 = rules.unary_expr()
    if not tonumber(const2) then
      semanticError(tab_ERRORMSG[25])
    end
    local const = const1 / const2
    return rules.mult_expr_l(const, numrule)
  elseif tab_firsts.rule_110[token] then
    recognize("%")
    local const2 = rules.unary_expr()
    if not tonumber(const2) then
      semanticError(tab_ERRORMSG[25])
    end
    local const = math.mod(const1, const2)
    return rules.mult_expr_l(const, numrule)
  elseif (
          tab_follow.rule_111[token] or
          tab_follow['rule_'..numrule][token] or
          (getID() == ':')
         )
  then
    --empty
    return const1
  else
    sinError(tab_ERRORMSG[18])
  end
end

rules.add_expr_l = function (const1, numrule)
  if tab_firsts.rule_104[token] then
    recognize("+")
    if not tonumber(const1) then
      semanticError(tab_ERRORMSG[25])
    end
    local const2 = rules.mult_expr(numrule)
    local const = const1 + const2
    return rules.add_expr_l(const, numrule)
  elseif tab_firsts.rule_105[token] then
    recognize("-")
    if not tonumber(const1) then
      semanticError(tab_ERRORMSG[25])
    end
    local const2 = rules.mult_expr(numrule)
    local const = const1 - const2
    return rules.add_expr_l(const, numrule)
  elseif (
          tab_follow.rule_106[token] or
          tab_follow['rule_'..numrule][token] or
          (getID() == ':')
         )
  then
    --empty
    return const1
  else
    sinError(tab_ERRORMSG[19])
  end
end

rules.shift_expr_l = function (const1, numrule)
  if tab_firsts.rule_100[token] then
    recognize(">>")
    rules.add_expr(numrule)
    rules.shift_expr_l(numrule)
  elseif tab_firsts.rule_101[token] then
    recognize("<<")
    rules.add_expr(numrule)
    rules.shift_expr_l(numrule)
  elseif (
          tab_follow.rule_102[token] or
          tab_follow['rule_'..numrule][token] or
          (getID() == ':')
         )
  then
    --empty
    return const1
  else
    sinError(tab_ERRORMSG[20])
  end
end

rules.and_expr_l = function (const1, numrule)
  if tab_firsts.rule_97[token] then
    recognize("&")
--[[   if not is_num(const1) then
      semanticError(tab_ERRORMSG[25])
    end]]
    local const2 = rulesshift_expr(numrule)
--    local const = const1 and const2
    return rules.and_expr_l(const, numrule)
  elseif (
          tab_follow.rule_98[token] or
          tab_follow['rule_'..numrule][token] or
          (getID() == ':')
         )
  then
    --empty
    return const1
  else
    sinError(tab_ERRORMSG[21])
  end
end

rules.xor_expr_l = function (numrule)
  if tab_firsts.rule_94[token] then
    recognize("^")
    rules.and_expr(numrule)
    rules.xor_expr_l(numrule)
  elseif (
          tab_follow.rule_95[token] or
          tab_follow['rule_'..numrule][token] or
          (getID() == ':')
         )
  then
    --empty
  else
    sinError(tab_ERRORMSG[22])
  end
end

rules.or_expr_l = function (numrule)
  if tab_firsts.rule_91[token] then
    recognize("|")
    rules.xor_expr(numrule)
    rules.or_expr_l(numrule)
  elseif (
          tab_follow['rule_'..numrule][token] or
          (getID() == ':')
         )
  then
    --empty
  else
    sinError(tab_ERRORMSG[23])
  end
end

rules.template_type_spec = function ()
  if tab_firsts.rule_58[token] then
    return rules.sequence_type()
  elseif tab_firsts.rule_59[token] then
    return rules.string_type()
  elseif tab_firsts.rule_60[token] then
    return rules.fixed_pt_type()
  end
end

rules.sequence_type = function ()
  recognize(lex.tab_tokens.TK_SEQUENCE, "'sequence'")
  recognize("<")
  local tab_type_spec = rules.simple_type_spec(61)
  tab_type_spec = rules.sequence_type_tail(tab_type_spec)
  if callbacks.sequence then
    callbacks.sequence(tab_type_spec)
  end
  return tab_type_spec
end

rules.sequence_type_tail = function (tab_type_spec)
  if tab_firsts.rule_69[token] then
    recognize(",")
    local const = rules.positive_int_const(69)
    recognize(">")
    return { _type = TAB_TYPEID.SEQUENCE, elementtype = tab_type_spec, maxlength = const  }
  elseif tab_firsts.rule_70[token] then
    recognize(">")
  --maxlength??
    return { _type = TAB_TYPEID.SEQUENCE, elementtype = tab_type_spec, maxlength = 0  }
  else
    sinError("',' or '>'")
  end
end

rules.string_type = function ()
  recognize(lex.tab_tokens.TK_STRING)
--maxlength??
  return TAB_BASICTYPE.STRING
end


rules.string_type_tail = function ()
  if tab_firsts.rule_72[token] then
    recognize("<")
    local const = positive_int_const(72)
    recognize(">")
    return const
  elseif tab_follow.rule_73[token] then
    return nil
    --empty
  else
    sinError(tab_ERRORMSG[26])
  end
end

rules.fixed_pt_type = function ()
  recognize(lex.tab_tokens.TK_FIXED)
  recognize("<")
  local const1 = rules.positive_int_const(74)
  recognize(",")
  local const2 = rules.positive_int_const(74)
  recognize(">")
  return TAB_BASICTYPE.FIXED
end

rules.constr_type_spec = function ()
  if tab_firsts.rule_33[token] then
    return rules.struct_type()
  elseif tab_firsts.rule_34[token] then
    return rules.union_type()
  elseif tab_firsts.rule_35[token] then
    return rules.enum_type()
  else
    sinError(tab_ERRORMSG[27])
  end
end

rules.struct_type = function ()
  recognize(lex.tab_tokens.TK_STRUCT)
  recognize(lex.tab_tokens.TK_ID)
  define(getID(), TAB_TYPEID.STRUCT)
  recognize("{")
  rules.member_l()
  local struct = currentScope
  gotoFatherScope()
  recognize("}")
  if callbacks.struct then
    callbacks.struct(struct)
  end
  return struct
end

rules.union_type = function ()
  if tab_firsts.rule_148[token] then
    recognize(lex.tab_tokens.TK_UNION)
    recognize(lex.tab_tokens.TK_ID)
    local union_name = getID()
    recognize(lex.tab_tokens.TK_SWITCH)
    define(union_name, TAB_TYPEID.UNION)
    recognize("(")
    currentScope.switch = rules.switch_type_spec()
    recognize(")")
    recognize("{")
    currentScope.default = -1
    rules.case_l()
    recognize("}")
    local union = currentScope
    gotoFatherScope()
    if callbacks.union then
      callbacks.union(union)
    end
    return tab_union
  else
    sinError(tab_ERRORMSG[29])
  end
end

rules.switch_type_spec = function ()
  if tab_firsts.rule_149[token] then
    return rules.integer_type(148)
  elseif tab_firsts.rule_150[token] then
    recognize(lex.tab_tokens.TK_LONG)
    return rules.long_e(148)
  elseif tab_firsts.rule_151[token] then
    recognize(lex.tab_tokens.TK_CHAR)
    return TAB_BASICTYPE.CHAR
  elseif tab_firsts.rule_152[token] then
    recognize(lex.tab_tokens.TK_BOOLEAN)
    return TAB_BASICTYPE.BOOLEAN
  elseif tab_firsts.rule_153[token] then
    recognize(lex.tab_tokens.TK_ENUM)
    return TAB_BASICTYPE.ENUM
  elseif tab_firsts.rule_154[token] then
    return rules.scoped_name(154)
  else
    sinError(tab_ERRORMSG[30])
  end
end

rules.case_l = function ()
  if tab_firsts.rule_155[token] then
    rules.case()
    rules.case_l_r()
  else
    sinError(tab_ERRORMSG[31])
  end
end

rules.case_l_r = function ()
  if tab_firsts.rule_156[token] then
    rules.case()
    rules.case_l_r()
  elseif tab_follow.rule_157[token] then
    --empty
  else
    sinError(tab_ERRORMSG[33])
  end
end

rules.case = function ()
  if tab_firsts.rule_158[token] then
    local cases = rules.case_label_l()
    local tab_type_spec, name = rules.element_spec(cases)
    for i, case in pairs(cases) do
      if i == 1 then
        dclName(name, currentScope, {type = tab_type_spec, label = case})
        registerID(name);
      else
        table.insert(currentScope, {name = name, type = tab_type_spec, label = case})
      end
      if case == 'none' then
        currentScope.default = table.getn(currentScope)
      end
    end
    recognize(";")
  else
    sinError(tab_ERRORMSG[31])
  end
end

rules.case_label_l = function ()
  local cases = {}
  if tab_firsts.rule_159[token] then
    rules.case_label(cases)
    rules.case_label_l_r(cases)
  else
    sinError(tab_ERRORMSG[31])
  end
  return cases
end

rules.case_label_l_r = function (cases)
  if tab_firsts.rule_160[token] then
    rules.case_label(cases)
    rules.case_label_l_r(cases)
  elseif tab_follow.rule_161[token] then
    --empty
  else
    sinError(tab_ERRORMSG[32])
  end
end

rules.case_label = function (cases)
  if (tab_firsts.rule_162[token]) then
    recognize(lex.tab_tokens.TK_CASE)
    local value = rules.positive_int_const(162)
    table.insert(cases, value)
  elseif (tab_firsts.rule_163[token]) then
    recognize(lex.tab_tokens.TK_DEFAULT)
    recognize(":")
    if (currentScope.default ~= -1) then
      semanticError("A default case can appear at most once.")
    else
      table.insert(cases, 'none')
      currentScope.default = 1
    end
  else
    sinError(tab_ERRORMSG[31])
  end
end

rules.case_label_aux = function ()
  if (token == lex.tab_tokens.TK_ID) then
    recognize(lex.tab_tokens.TK_ID)
    tab_scope = getDefinition(getID())
    recognize(":")
    return rules.case_label_tail(tab_scope)
  elseif (token == ':') then
    recognize(":")
    recognize(":")
    recognize(lex.tab_tokens.TK_ID, "identifier")
    tab_scope = getDefinition(getID())
    recognize(":")
    return rules.case_label_tail(tab_scope)
  end
end

rules.case_label_tail = function (tab_scope)
  if (token == ':') then
    recognize(":")
    return rules.case_label_tail_aux(tab_scope)
  elseif (tab_firsts.rule_28[token] or tab_firsts.rule_29[token]) then
    --empty
    return tab_scope
  end
end

rules.case_label_tail_aux = function (tab_scope)
  if (token == ':') then
    recognize(":")
  elseif (token == lex.tab_tokens.TK_ID) then
    recognize(lex.tab_tokens.TK_ID)
    local namespace = getID()
    tab_scope = getDefinition(namespace, tab_scope.absolute_name)
    tab_scope = rules.case_label_tail_aux(tab_scope)
  end
  return tab_scope
end

rules.element_spec = function (cases)
  if (tab_firsts.rule_164[token]) then
    local tab_type_spec = rules.type_spec(221)
    recognize(lex.tab_tokens.TK_ID)
    local name = getID()
    return tab_type_spec, name
  else
    sinError(tab_ERRORMSG[03])
  end
end

rules.enum_type = function ()
  recognize(lex.tab_tokens.TK_ENUM)
  recognize(lex.tab_tokens.TK_ID)
  local _, tab_enum = define(getID(), TAB_TYPEID.ENUM)
  recognize("{")
  rules.enumerator(tab_enum)
  rules.enumerator_l(tab_enum)
  recognize("}")
  if callbacks.enum then
    callbacks.enum(tab_enum)
  end
  return tab_enum
end

rules.enumerator = function (tab_enum)
  recognize(lex.tab_tokens.TK_ID)
  local name = getID()
  dclName(name, tab_enum)
  registerID(name);
end

rules.enumerator_l = function (tab_enum)
  if (tab_firsts.rule_166[token]) then
    recognize(",")
    rules.enumerator(tab_enum)
    rules.enumerator_l(tab_enum)
  elseif (tab_follow.rule_167[token]) then
    -- empty
  else
    sinError("',' or '}'")
  end
end

rules.module = function ()
  if (tab_firsts.rule_305[token]) then
    recognize(lex.tab_tokens.TK_MODULE)
    recognize(lex.tab_tokens.TK_ID)
    local name = getID()
    if (name == 'CORBA') then
      CORBAVisible = true
    end
    local status, _module = define(name, TAB_TYPEID.MODULE)
    recognize("{")
    rules.definition_l_module()
    local module = currentScope
    gotoFatherScope()
    recognize("}")
    if callbacks.module then
      callbacks.module(module)
    end
  end
end

rules.long_or_double = function ()
  if tab_firsts.rule_55[token] then
    recognize(lex.tab_tokens.TK_LONG)
    return TAB_BASICTYPE.LLONG
  elseif tab_firsts.rule_56[token] then
    recognize(lex.tab_tokens.TK_DOUBLE)
    return TAB_BASICTYPE.LDOUBLE
  else
    return TAB_BASICTYPE.LONG
  end
end

rules.scoped_name_l = function (tab_scope, full_namespace, num_follow_rule)
  if (token == ":") then
    recognize(":")
    recognize(":")
    recognize(lex.tab_tokens.TK_ID)
    local namespace = getID()
    full_namespace = tab_scope.absolute_name..'::'..namespace
    tab_scope = getDefinition(namespace, tab_scope.absolute_name)
    tab_scope = rules.scoped_name_l(tab_scope, full_namespace, num_follow_rule)
  elseif (tab_follow['rule_'..num_follow_rule][token]) then
    -- empty
  else
    sinError("':' or "..tab_follow_rule_error_msg[num_follow_rule])
  end
  return tab_scope
end

rules.scoped_name = function (num_follow_rule)
  local name = ''
  local tab_scope = {}
  if (token == lex.tab_tokens.TK_ID) then
    recognize(lex.tab_tokens.TK_ID)
    name = getID()
    tab_scope = getDefinition(name)
    tab_scope = rules.scoped_name_l(tab_scope, name, num_follow_rule)
  elseif (token == ":") then
    recognize(":")
    recognize(":")
    recognize(lex.tab_tokens.TK_ID)
    name = getID()
    tab_scope = getDefinition(name)
    tab_scope = rules.scoped_name_l(tab_scope, name, num_follow_rule)
  end
  local absolute_name 
  if (tab_scope.absolute_name) then
    absolute_name = tab_scope.absolute_name
    registerID(tab_scope.absolute_name)
  else
  end
  return tab_scope
end

rules.union_or_struct = function ()
  if (tab_firsts.rule_168[token]) then
    recognize(lex.tab_tokens.TK_STRUCT)
    recognize(lex.tab_tokens.TK_ID)
    local name = getID()
    return rules.struct_tail(name)
  elseif (tab_firsts.rule_169[token]) then
    recognize(lex.tab_tokens.TK_UNION)
    recognize(lex.tab_tokens.TK_ID)
    define(getID(), TAB_TYPEID.UNION)
    rules.union_tail()
    local union = currentScope
    gotoFatherScope()
    if callbacks.union then
      callbacks.union(union)
    end
    return union
  else
    sinError("'struct' or 'union'")
  end
end

rules.struct_tail = function (name)
  if (tab_firsts.rule_170[token]) then
    define(name, TAB_TYPEID.STRUCT)
    recognize("{")
    rules.member_l()
    recognize("}")
    local struct = currentScope
    gotoFatherScope()
    if callbacks.struct then
      callbacks.struct(struct)
    end
    return struct
  elseif (token == ";") then
    return dclForward(name, TAB_TYPEID.STRUCT)
  else
    sinError(" '{' or ';' ")
  end
end

rules.member_l = function ()
  if (tab_firsts.rule_137[token]) then
    rules.member()
    rules.member_r()
  else
    sinError(tab_ERRORMSG[03])
  end
end

rules.member = function ()
  if (tab_firsts.rule_140[token]) then
    rules.declarator_l(rules.type_spec())
    recognize(";")
  else
    sinError(tab_ERRORMSG[03])
  end
end

rules.member_r = function ()
  if tab_firsts.rule_138[token] then
    rules.member()
    rules.member_r()
  elseif tab_follow.rule_139[token] then
    -- empty
  else
    sinError(tab_ERRORMSG[28])
  end
end

rules.declarator_l = function (type, access)
  rules.declarator(type, access)
  rules.declarator_l_r(type, access)
end

rules.declarator_l_r = function (type, access)
  if (tab_firsts.rule_142[token]) then
    recognize(",")
    rules.declarator(type, access)
    rules.declarator_l_r(type, access)
  elseif (tab_follow.rule_143[token]) then
    --empty
  else
    sinError(tab_ERRORMSG[11])
  end
end

rules.declarator = function (type, access)
  recognize(lex.tab_tokens.TK_ID)
  local name = getID()
  dclName(name, currentScope, 
  {
    type = rules.fixed_array_size_l(type),
    access = access,
  })
  registerID(name);
end

rules.union_tail = function ()
  if (tab_firsts.rule_172[token]) then
    recognize(lex.tab_tokens.TK_SWITCH)
    recognize("(")
    currentScope.switch  = rules.switch_type_spec()
    recognize(")")
    recognize("{")
    currentScope.default = -1
    rules.case_l()
    recognize("}")
  else
    sinError("'switch'")
  end
end

rules.except_dcl = function ()
  recognize(lex.tab_tokens.TK_EXCEPTION)
  recognize(lex.tab_tokens.TK_ID)
  local name = getID()
  define(name, TAB_TYPEID.EXCEPTION)
  recognize("{")
  rules.member_l_empty()
  local except = currentScope
  gotoFatherScope()
  recognize("}")
  if callbacks.except then
    callbacks.except(except)
  end
end

rules.member_l_empty = function ()
  if (tab_firsts.rule_187[token]) then
    rules.member()
    rules.member_l_empty()
  elseif (token == "}") then
    -- empty
  else
    sinError("member list { ... } or '}'")
  end
end

rules.definition_l_r_module = function ()
  if (tab_firsts.rule_12[token]) then
    rules.definition()
    rules.definition_l_r_module()
  elseif (token == '}') then
    -- empty
  else
    sinError("definition")
  end
end

rules.definition_l_module = function ()
  if (tab_firsts.rule_11[token]) then
    rules.definition()
    rules.definition_l_r_module()
  else
    sinError("definition")
  end
end


---
-- INTERFACE DECLARATION
--------------------------------------------------------------------------

rules.inter_value_event = function ()
  if (tab_firsts.rule_192[token]) then
    recognize(lex.tab_tokens.TK_INTERFACE)
    recognize(lex.tab_tokens.TK_ID)
    local name = getID()
    local interface = rules.interface_tail(name)
    if callbacks.interface then
      callbacks.interface(interface)
    end
  elseif (tab_firsts.rule_189[token]) then
    recognize(lex.tab_tokens.TK_ABSTRACT)
    rules.abstract_tail()
  elseif (tab_firsts.rule_190[token]) then
    recognize(lex.tab_tokens.TK_LOCAL)
    recognize(lex.tab_tokens.TK_INTERFACE)
    recognize(lex.tab_tokens.TK_ID)
    local name = getID()
    local interface = rules.interface_tail(name, 'local')
    if callbacks.interface and interface then
      callbacks.interface(interface)
    end
  elseif (tab_firsts.rule_193[token]) then
    recognize(lex.tab_tokens.TK_VALUETYPE)
    recognize(lex.tab_tokens.TK_ID)
    local name = getID()
    rules.value_tail(name)
  elseif (tab_firsts.rule_191[token]) then
    recognize(lex.tab_tokens.TK_CUSTOM)
    rules.value_or_event()
  elseif tab_firsts.rule_194[token] then
    recognize(lex.tab_tokens.TK_EVENTTYPE)
    recognize(lex.tab_tokens.TK_ID)
    local name = getID()
    local tab_eventtypescope = rules.eventtype_tail(name)
    if callbacks.eventtype then
      callbacks.eventtype(tab_eventtypescope)
    end
  else
    sinError("'interface', 'abstract', 'local' or 'valuetype'")
  end
end

rules.abstract_tail = function ()
  if (tab_firsts.rule_195[token]) then
    recognize(lex.tab_tokens.TK_INTERFACE)
    recognize(lex.tab_tokens.TK_ID)
    local name = getID()
    local interface = rules.interface_tail(name, 'abstract')
    if callbacks.interface then
      callbacks.interface(interface)
    end
  elseif (tab_firsts.rule_196[token]) then
    recognize(lex.tab_tokens.TK_VALUETYPE)
    recognize(lex.tab_tokens.TK_ID)
    local name = getID()
    rules.value_tail(name, "abstract")
  elseif tab_firsts.rule_197[token] then
    recognize(lex.tab_tokens.TK_EVENTTYPE)
    recognize(lex.tab_tokens.TK_ID)
    local name = getID()
    local tab_eventtypescope = rules.eventtype_tail(name, "abstract")
    if callbacks.eventtype then
      callbacks.eventtype(tab_eventtypescope)
    end
  else
    sinError("'interface', 'valuetype' or 'event'")
  end
end

rules.interface_tail = function (name, header)
  if (tab_firsts.rule_198[token]) then
    recognize(":")
    local base = rules.scoped_name(204)
    define(name, TAB_TYPEID.INTERFACE)
    table.insert(currentScope, base)
    rules.bases()
    recognize("{")
    rules.export_l()
    recognize("}")
    local interface = currentScope
    rules.verifyHeader(header)
    gotoFatherScope()
    return interface
  elseif (tab_firsts.rule_199[token]) then
    recognize("{")
    define(name, TAB_TYPEID.INTERFACE)
    rules.export_l()
    recognize("}")
    local interface = currentScope
    rules.verifyHeader(header)
    gotoFatherScope()
    return interface
  elseif (token == ';') then
    return dclForward(name, TAB_TYPEID.INTERFACE)
  else
    sinError("'{', ':' or ';'")
  end
end

rules.bases = function ()
  if (tab_firsts.rule_254[token]) then
    recognize(",")
    local base = rules.scoped_name(204)
    table.insert(currentScope, base)
    rules.bases()
  elseif (token == '{') then
    -- empty
  else
    sinError("',' or '{'")
  end
end

rules.verifyHeader = function (header)
  if (header == 'local') then
    currentScope['header'] = true
  elseif (header == 'abstract') then
    currentScope['abstract'] = true
  end
end

rules.export_l = function ()
  if (tab_firsts.rule_207[token]) then
    rules.export()
    rules.export_l()
  elseif (token == "}") then
    --empty
  else
    sinError("empty interface, a declaration or '}'")
  end
end

rules.export = function ()
  if (tab_firsts.rule_209[token]) then
    rules.type_dcl()
    recognize(";")
  elseif (tab_firsts.rule_210[token]) then
    rules.const_dcl()
    recognize(";")
  elseif (tab_firsts.rule_211[token]) then
    rules.except_dcl()
    recognize(";")
  elseif (tab_firsts.rule_212[token]) then
    rules.attr_dcl()
    recognize(";")
  elseif (tab_firsts.rule_213[token]) then
    rules.op_dcl()
    recognize(";")
  else
    sinError("constant, type, exception, attribute or operation declaration")
  end
end


---
-- OPERATION DECLARATION
--------------------------------------------------------------------------

rules.op_dcl = function ()
  if (tab_firsts.rule_243[token]) then
    recognize(lex.tab_tokens.TK_ONEWAY)
    local result = rules.op_type_spec()
    if (result._type ~= 'void') then
      semanticError("An operation with the oneway attribute must specify a 'void' return type.")
    end
    recognize(lex.tab_tokens.TK_ID)
    local name = getID()
    define(name, TAB_TYPEID.OPERATION)
    currentScope.name = name
    currentScope.oneway = true
    rules.parameter_dcls()
    rules.raises_expr_e(currentScope)
    rules.context_expr_e()
    local operation = currentScope
    gotoFatherScope()
    if (callbacks.operation) then
      callbacks.operation(operation)
    end
  elseif tab_firsts.rule_244[token] then
    local result = rules.op_type_spec()
    recognize(lex.tab_tokens.TK_ID)
    local name = getID()
    define(name, TAB_TYPEID.OPERATION)
    currentScope.name = name
    currentScope.result = result
    rules.parameter_dcls()
    rules.raises_expr_e(currentScope)
    rules.context_expr_e()
    local operation = currentScope
    gotoFatherScope()
    if callbacks.operation then
      callbacks.operation(operation)
    end
  else
    sinError("'oneway' or type specification")
  end
end

rules.op_type_spec = function ()
  if (tab_firsts.rule_245[token]) then
    return rules.param_type_spec()
  elseif (tab_firsts.rule_246[token]) then
    recognize(lex.tab_tokens.TK_VOID)
    return TAB_BASICTYPE.VOID
  else
    sinError("type return")
  end
end

rules.parameter_dcls = function ()
  recognize("(")
  rules.parameter_dcls_tail()
end

rules.parameter_dcls_tail = function ()
  if (tab_firsts.rule_248[token]) then
    currentScope.parameters = {}
    rules.param_dcl()
    rules.param_dcl_l()
    recognize(")")
  elseif (tab_firsts.rule_249[token]) then
    recognize(")")
  else
    sinError("'in', 'out', 'inout' or ')'")
  end
end

rules.param_dcl = function ()
  local attribute = rules.param_attribute()
  local type = rules.param_type_spec()
  recognize(lex.tab_tokens.TK_ID)
  local name = getID()
  dclName(name, currentScope.parameters, {mode = attribute, type = type})
  registerID(name);
end

rules.param_dcl_l = function ()
  if (tab_firsts.rule_254[token]) then
    recognize(",")
    rules.param_dcl()
    rules.param_dcl_l()
  elseif token == lex.tab_tokens.TK_RAISES or
       token == lex.tab_tokens.TK_CONTEXT or
       token == ')' then
    -- empty
  else
    sinError("',', ')', 'raises' or 'context'")
  end
end

rules.param_attribute = function ()
  if (tab_firsts.rule_251[token]) then
    recognize(lex.tab_tokens.TK_IN)
    return 'PARAM_IN'
  elseif (tab_firsts.rule_252[token]) then
    recognize(lex.tab_tokens.TK_OUT)
    return 'PARAM_OUT'
  elseif (tab_firsts.rule_253[token]) then
    recognize(lex.tab_tokens.TK_INOUT)
    return 'PARAM_INOUT'
  end
end

rules.param_type_spec = function ()
  if (tab_firsts.rule_219[token]) then
    return rules.base_type_spec()
  elseif (tab_firsts.rule_220[token]) then
    return rules.string_type()
  elseif (tab_firsts.rule_221[token]) then
    return rules.scoped_name(221)
  else
    sinError('type specification')
  end
end

rules.raises_expr = function (tab)
  recognize(lex.tab_tokens.TK_RAISES)
  recognize("(")
  tab.exceptions = {}
  rules.raises(tab.exceptions)
  rules.inter_name_seq(tab.exceptions)
  recognize(")")
end

rules.raises = function (raises)
  local exception = rules.scoped_name(229)
  if (exception._type ~= TAB_TYPEID.EXCEPTION) then
    semanticError(string.format("The type of '%s' is %s, but it should be exception.",
          exception.absolute_name, exception._type))
  end
  table.insert(raises, exception)
end

rules.inter_name_seq = function (_raises)
  if (tab_firsts.rule_254[token]) then
    recognize(",")
    rules.raises(_raises)
    rules.inter_name_seq(_raises)
  elseif (token == ')') then
    -- empty
  else
    sinError("')'")
  end
end

rules.raises_expr_e = function (tab)
  if (tab_firsts.rule_370[token]) then
    rules.raises_expr(tab)
  elseif (token == ';' or token == lex.tab_tokens.TK_CONTEXT) then
    -- empty
  else
    sinError("'raises', 'context', ';'")
  end
end

rules.context_expr_e = function ()
  if (tab_firsts.rule_377[token]) then
    rules.context_expr()
  elseif (token == ';') then
    -- empty
  else
    sinError("'context' or ';'")
  end
end

rules.context_expr = function ()
  recognize(lex.tab_tokens.TK_CONTEXT)
  recognize("(")
  currentScope.contexts = {}
  rules.context()
  rules.string_literal_l()
  recognize(")")
end

rules.context = function ()
  recognize(lex.tab_tokens.TK_STRING_LITERAL)
  local name = getID()
  dclName(name, currentScope.contexts, {})
  registerID(name);
end

rules.string_literal_l = function ()
  if (tab_firsts.rule_257[token]) then
    recognize(",")
    rules.context()
    rules.string_literal_l()
  elseif (token == ')') then
    -- empty
  else
    sinError("',' or ')'")
  end
end


---
-- ATTRIBUTE
--------------------------------------------------------------------------

rules.attr_dcl = function ()
  if (tab_firsts.rule_216[token]) then
    rules.readonly_attr_spec()
  elseif (tab_firsts.rule_217[token]) then
    rules.attr_spec()
  else
    sinError("'readonly' or 'attribute'")
  end
end

rules.readonly_attr_spec = function ()
  recognize(lex.tab_tokens.TK_READONLY)
  recognize(lex.tab_tokens.TK_ATTRIBUTE)
  local type = rules.param_type_spec()
  rules.readonly_attr_spec_dec(type)
end

rules.attr_spec = function ()
  recognize(lex.tab_tokens.TK_ATTRIBUTE)
  local type = rules.param_type_spec()
  rules.attr_declarator(type)
end

rules.readonly_attr_spec_dec = function (type)
  local attribute = {type = type, readonly = true}
  local name = rules.simple_dcl()
  define(name, TAB_TYPEID.ATTRIBUTE, attribute)
  rules.readonly_attr_spec_dec_tail(attribute)
  if callbacks.attribute then
    callbacks.attribute(attribute)
  end
end

rules.attr_declarator = function (type)
  local attribute = {type = type}
  local name = rules.simple_dcl()
  define(name, TAB_TYPEID.ATTRIBUTE, attribute)
  rules.attr_declarator_tail(attribute)
  if callbacks.attribute then
    callbacks.attribute(attribute)
  end
end

rules.readonly_attr_spec_dec_tail = function (attribute)
  if (tab_firsts.rule_227[token]) then
    rules.raises_expr(attribute)
  elseif (tab_firsts.rule_228[token]) then
    rules.simple_dcl_l(type, true)
  elseif (token == ';') then
    -- empty
  else
    sinError("'raises', ',' or ';'")
  end
end

rules.attr_declarator_tail = function (attribute)
  if (tab_firsts.rule_234[token]) then
    rules.attr_raises_expr(attribute)
  elseif (tab_firsts.rule_235[token]) then
    rules.simple_dcl_l(attribute.type)
  elseif (token == ';') then
    -- empty
  else
    sinError("'getraises', 'setraises', ',' or ';'")
  end
end

rules.simple_dcl = function ()
  recognize(lex.tab_tokens.TK_ID)
  return getID()
end

rules.simple_dcl_l = function (type, readonly)
  if (tab_firsts.rule_142[token]) then
    recognize(",")
    local attribute = {type = type, readonly = readonly}
    local name = rules.simple_dcl()
    define(name, TAB_TYPEID.ATTRIBUTE, attribute)
    rules.simple_dcl_l(type)
  elseif (token == ';') then
    -- empty
  end
end

rules.attr_raises_expr = function (attribute)
  if (tab_firsts.rule_236[token]) then
    recognize(lex.tab_tokens.TK_GETRAISES)
    attribute.raises = {}
    rules.exception_l(attribute, 'getraises')
    rules.attr_raises_expr_tail(attribute)
  elseif (tab_firsts.rule_237[token]) then
    recognize(lex.tab_tokens.TK_SETRAISES)
    attribute.raises = {}
    rules.exception_l(attribute, 'setraises')
  end
end

rules.attr_raises_expr_tail = function (attribute)
  if (tab_firsts.rule_238[token]) then
    recognize(lex.tab_tokens.TK_SETRAISES)
    rules.exception_l(attribute, 'setraises')
  elseif (token == ';') then
    --empty
  else
    sinError("'setraises' or ';'")
  end
end

rules.exception = function (attribute, raises_type)
  local exception = {type = raises_type, exception = rules.scoped_name(229)}
  table.insert(attribute.raises, exception)
end

rules.exception_l = function (attribute, raises_type)
  recognize("(")
  rules.exception(attribute, raises_type)
  rules.exception_l_seq(attribute, raises_type)
  recognize(")")
end

rules.exception_l_seq = function (attribute, raises_type)
  if (tab_firsts.rule_142[token]) then
    recognize(",")
    rules.exception(attribute, raises_type)
    rules.exception_l_seq(attribute, raises_type)
  elseif (token == ';') then
    -- empty
  end
end


---
-- COMPONENT DECLARATION
--------------------------------------------------------------------------

rules.component = function ()
  recognize(lex.tab_tokens.TK_COMPONENT)
  recognize(lex.tab_tokens.TK_ID)
  local name = getID()
  define(name, TAB_TYPEID.COMPONENT)
  currentScope.declarations = {}
  rules.component_tail(name)
  gotoFatherScope()
end

rules.component_tail = function (name)
  if (tab_firsts.rule_307[token]) then
    recognize(":", "':'")
    local component = rules.scoped_name(307)
    if component._type ~= TAB_TYPEID.COMPONENT then
      semanticError("The previously-defined type is not a COMPONENT")
    end
    currentScope.component_base = component
    rules.supp_inter_spec(308)
    recognize("{")
    rules.component_body()
    recognize("}")
  elseif (tab_firsts.rule_308[token]) then
    rules.supp_inter_spec(308)
    recognize("{")
    rules.component_body()
    recognize("}")
  elseif (tab_firsts.rule_309[token]) then
    recognize("{")
    rules.component_body()
    recognize("}")
  elseif (token == ';') then
    dclForward(name, TAB_TYPEID.COMPONENT)
    --empty
  else
    sinError("':', 'supports' or '{'")
  end
end

rules.supp_inter_spec = function (num_follow_rule)
  if tab_firsts.rule_316[token] then
    recognize(lex.tab_tokens.TK_SUPPORTS)
    currentScope.supports = {}
    local interface = rules.scoped_name(num_follow_rule)
    if (interface._type ~= TAB_TYPEID.INTERFACE) then
      semanticError("The 'SUPPORTS' construction must be reference to an interface")
    end
    table.insert(currentScope.supports, interface)
    rules.supp_name_list(num_follow_rule)
  elseif (tab_follow['rule_'..num_follow_rule][token]) then
    -- empty
  else
    sinError("':', ',', or "..tab_follow_rule_error_msg[num_follow_rule])
  end
end

rules.supp_name_list = function (num_follow_rule)
  if (tab_firsts.rule_321[token]) then
    recognize(',')
    local interface = rules.scoped_name(num_follow_rule)
    if (interface._type ~= TAB_TYPEID.INTERFACE) then
      semanticError("The 'SUPPORTS' construction must be reference to an interface")
    end
    table.insert(currentScope.supports, interface)
    rules.supp_name_list(num_follow_rule)
  elseif (tab_follow['rule_'..num_follow_rule][token]) then
    --empty
  else
    sinError("',' or '{'")
  end
end

rules.component_body = function ()
  if (tab_firsts.rule_323[token]) then
    rules.component_export()
    rules.component_body()
  elseif (token == '}') then
    --empty
  else
    sinError("'provides', 'uses', 'emits', 'publishes', 'consumes', 'readonly' 'attribute' or '}'")
  end
end

rules.component_export = function ()
  if (tab_firsts.rule_325[token]) then
    rules.provides_dcl()
    recognize(';')
  elseif (tab_firsts.rule_326[token]) then
    rules.uses_dcl()
    recognize(';')
  elseif (tab_firsts.rule_327[token]) then
    rules.emits_dcl()
    recognize(';')
  elseif (tab_firsts.rule_328[token]) then
    rules.publishes_dcl()
    recognize(';')
  elseif (tab_firsts.rule_329[token]) then
    rules.consumes_dcl()
    recognize(';')
  elseif (tab_firsts.rule_330[token]) then
    rules.attr_dcl()
    recognize(';')
  end
end

rules.provides_dcl = function ()
  recognize(lex.tab_tokens.TK_PROVIDES, 'provides')
  local tab_provides = { _type = 'provides' }
  tab_provides.interface_type = rules.interface_type()
  recognize(lex.tab_tokens.TK_ID, '<identifier>')
  local name = getID()
--  new_name(name, name, currentScope.declarations, tab_provides, ERRMSG_DECLARED, name)
end

rules.interface_type = function ()
  if (tab_firsts.rule_332[token]) then
    local scope = rules.scoped_name(332)
    if (scope._type ~= TAB_TYPEID.INTERFACE) then
      semanticError("The interface type of this provides declaration shall be either the keyword \
                Object or a scoped name that denotes a previously-declared interface type")
    end
    return scope
  elseif (tab_firsts.rule_333[token]) then
    recognize(lex.tab_tokens.TK_OBJECT)
    return TAB_BASICTYPE.OBJECT
  else
    sinError("<identifier> or 'Object'")
  end
end

rules.uses_dcl = function ()
  recognize(lex.tab_tokens.TK_USES)
  local tab_uses = { _type = 'uses' }
  tab_uses.multiple = rules.multiple_e()
  tab_uses.interface_type = rules.interface_type()
  recognize(lex.tab_tokens.TK_ID)
  local name = getID()
--  new_name(name, name, currentScope.declarations, tab_uses, ERRMSG_DECLARED, name)
end

rules.multiple_e = function ()
  if (tab_firsts.rule_339[token]) then
    recognize(lex.tab_tokens.TK_MULTIPLE)
    return true
  elseif (tab_follow.rule_340[token]) then
    return nil
    --empty
  else
    sinError("'multiple', <identifier>, ':' or 'Object'")
  end
end

rules.emits_dcl = function ()
  recognize(lex.tab_tokens.TK_EMITS)
  local name = getID()
  local tab_uses = { _type = 'emits' }
--  new_name(name, name, currentScope.declarations, tab_emits, ERRMSG_DECLARED, name)
  tab_uses.event_type = rules.scoped_name(341)
  recognize(lex.tab_tokens.TK_ID)
  tab_uses.evtsrc = getID()
end

rules.publishes_dcl = function ()
  recognize(lex.tab_tokens.TK_PUBLISHES)
  local name = getID()
  local tab_publishes = { _type = 'publishes' }
--  new_name(name, name, currentScope.declarations, tab_publishes, ERRMSG_DECLARED, name)
  tab_uses.event_type = rules.scoped_name(342)
  recognize(lex.tab_tokens.TK_ID)
  tab_uses.evtsrc = getID()
end

rules.consumes_dcl = function ()
  recognize(lex.tab_tokens.TK_CONSUMES)
  local name = getID()
  local tab_publishes = { _type = 'consumes' }
--  new_name(name, name, currentScope.declarations, tab_consumes, ERRMSG_DECLARED, name)
  tab_uses.event_type = rules.scoped_name(343)
  recognize(lex.tab_tokens.TK_ID)
  tab_uses.evtsink = getID()
end


---
-- HOME DECLARATION
--------------------------------------------------------------------------

rules.home_dcl = function ()
  recognize(lex.tab_tokens.TK_HOME)
  recognize(lex.tab_tokens.TK_ID)
  local name = getID()
  define(name, TAB_TYPEID.HOME)
  rules.home_dcl_tail(name)
  gotoFatherScope()
end

rules.home_dcl_tail = function (name)
  if (tab_firsts.rule_345[token])then
    rules.home_inh_spec()
    rules.supp_inter_spec(345)
    recognize(lex.tab_tokens.TK_MANAGES)
    local component = rules.scoped_name(347)
    currentScope.manages = component
    rules.primary_key_spec_e()
    recognize("{")
    rules.home_export_l()
    recognize("}")
  elseif (tab_firsts.rule_346[token]) then
    rules.supp_inter_spec(345)
    recognize(lex.tab_tokens.TK_MANAGES)
    local component = rules.scoped_name(347)
    currentScope.manages = component
    rules.primary_key_spec_e()
    recognize("{")
    rules.home_export_l()
    recognize("}")
  elseif (tab_firsts.rule_347[token]) then
    recognize(lex.tab_tokens.TK_MANAGES)
    currentScope.component = rules.scoped_name(347)
    rules.primary_key_spec_e()
    recognize("{")
    rules.home_export_l()
    recognize("}")
  else
    sin.error("'supports', 'manages', ':'")
  end
end

rules.home_inh_spec = function ()
  if (tab_firsts.rule_348[token]) then
    recognize(":")
    local home = rules.scoped_name(348)
    if (home._type ~= TAB_TYPEID.HOME) then
      semanticError("The previously-defined type is not a HOME")
    end
    currentScope.home_base = home
  end
end

--(353) <primary_key_spec_e>    :=    TK_PRIMARYKEY <scoped_name>
--(354)                         |     empty
rules.primary_key_spec_e = function ()
  if tab_firsts.rule_353[token] then
    recognize(lex.tab_tokens.TK_PRIMARYKEY, 'primarykey')
    rules.scoped_name(353)
  elseif tab_follow.rule_353[token] then
    --empty
  end
end

rules.home_export_l = function ()
  if tab_firsts.rule_359[token] then
    rules.home_export()
    rules.home_export_l()
  elseif tab_follow.rule_359[token] then
    --empty
  end
end

rules.home_export = function ()
  if tab_firsts.rule_361[token] then
    rules.export()
  elseif tab_firsts.rule_362[token] then
    rules.factory_dcl()
    recognize(";")
  elseif tab_firsts.rule_363[token] then
    rules.finder_dcl()
    recognize(";")
  else
    sinError("error")
  end
end

rules.factory_dcl = function ()
  if tab_firsts.rule_364[token] then
    recognize(lex.tab_tokens.TK_FACTORY)
    recognize(lex.tab_tokens.TK_ID)
    local name = getID()
    define(name, TAB_TYPEID.FACTORY)
    recognize("(")
    rules.init_param_dcls()
    recognize(")")
    rules.raises_expr_e()
  end
end

rules.init_param_dcls = function ()
  if tab_firsts.rule_366[token] then
    currentScope.members = {}
    rules.init_param_dcl()
    rules.init_param_dcl_list()
  elseif tab_follow.rule_367[token] then
    --empty
  end
end

rules.init_param_dcl = function ()
  if tab_firsts.rule_297[token] then
    recognize(lex.tab_tokens.TK_IN)
    local tab_type_spec = rules.param_type_spec()
    recognize(lex.tab_tokens.TK_ID)
    local param_name = getID()
    dclName(param_name, currentScope.members, 
      {
        type = tab_type_spec,
        name = param_name,
      })
  else
    sinError("'in'")
  end
end

rules.init_param_dcl_list = function ()
  if tab_firsts.rule_368[token] then
    recognize(",")
    rules.init_param_dcl()
    rules.init_param_dcl_list()
  elseif tab_follow.rule_369[token] then
    --empty
  end
end

rules.finder_dcl = function ()
  if tab_firsts.rule_365[token] then
    recognize(lex.tab_tokens.TK_FINDER)
    recognize(lex.tab_tokens.TK_ID)
    local name = getID()
    local tab_finder = { _type = TAB_TYPEID.FINDER, name = name }
--    new_name(name, name,
--           currentScope.members, tab_finder, ERRMSG_OPDECLARED, name)
    recognize("(")
    rules.init_param_dcls(tab_finder)
    recognize(")")
    rules.raises_expr_e(tab_finder)
  else
    sinError("'finder'")
  end
end

rules.value_or_event = function ()
  if (tab_firsts.rule_281[token]) then
    recognize(lex.tab_tokens.TK_VALUETYPE)
    recognize(lex.tab_tokens.TK_ID)
    local name = getID()
    rules.value_tail(name, "custom")
  elseif (tab_firsts.rule_282[token]) then
    recognize(lex.tab_tokens.TK_EVENTTYPE)
    recognize(lex.tab_tokens.TK_ID)
    local name = getID()
    local tab_eventtypescope = rules.eventtype_tail(name, "custom")
    if callbacks.eventtype then
      callbacks.eventtype(tab_eventtypescope)
    end
  else
    sinError("'valuetype' or 'eventtype'")
  end
end


---
-- VALUE DECLARATION
--------------------------------------------------------------------------

rules.value_tail = function (name, modifier)
  if (tab_firsts.rule_299[token]) then
    define(name, TAB_TYPEID.VALUETYPE)
    if modifier then
      currentScope[modifier] = true
    end
    local tab_valuetypescope = rules.value_tail_aux(name)
    if callbacks.valuetype then
      callbacks.valuetype(tab_valuetypescope)
    end
    return tab_valuetypescope
  elseif (tab_firsts.rule_298[token]) then
    define(name, TAB_TYPEID.VALUETYPE)
    if modifier then
      currentScope[modifier] = true
    end
    rules.value_inhe_spec()
    local tab_valuetypescope = rules.value_tail_aux(name)
    if callbacks.valuetype then
      callbacks.valuetype(tab_valuetypescope)
    end  
    return tab_valuetypescope
  elseif tab_firsts.rule_300[token] then
    local _, nameSpace = define(name, TAB_TYPEID.VALUEBOX)
    if modifier then
      nameSpace[modifier] = true
    end
    nameSpace.original_type = rules.type_spec()
    if callbacks.valuebox then
      callbacks.valuebox(nameSpace)
    end  
    return nameSpace
  elseif tab_follow.rule_301[token] then
    return dclForward(name, TAB_TYPEID.VALUETYPE)
  end
end

rules.value_tail_aux = function (name)
    recognize("{")
    rules.value_element_l()
    recognize("}")
    local tab_valuetypescope = currentScope
    gotoFatherScope()
    return tab_valuetypescope
end

rules.value_inhe_spec = function ()
  if tab_firsts.rule_268[token] then
    recognize(":")
    local truncatable = rules.truncatable_e()
    local value = rules.scoped_name(268)
    if (value._type ~= TAB_TYPEID.VALUETYPE and value._type ~= TAB_TYPEID.INTERFACE) then
      semanticError("The previously-defined type is not a VALUETYPE or INTERFACE")
    end
    currentScope.truncatable = truncatable
    if (not value.abstract) then
      currentScope.base_value = value
    else
      currentScope.abstract_base_values = {}
      table.insert(currentScope.abstract_base_values, value)
    end
    rules.value_name_list()
    rules.supp_inter_spec(308)
  elseif tab_firsts.rule_269[token] then
    rules.supp_inter_spec(308)
  else
    sinError("':', 'supports'")
  end
end

rules.value_name_list = function ()
  if tab_firsts.rule_277[token] then
    recognize(",")
    local value = rules.scoped_name(268)
    if (not value.abstract) then
      if (currentScope.base_value) then
        sinError("The single base concrete has been declared.")
      else
        sinError("The single base concrete must be the first element specified in the inheritance list.")
      end        
    else
      currentScope.abstract_base_values = currentScope.abstract_base_values or {}
      table.insert(currentScope.abstract_base_values, value)
    end  
    rules.value_name_list()
  elseif tab_follow.rule_278[token] then
    --empty
  end
end

rules.truncatable_e = function ()
  if tab_firsts.rule_271[token] then
    recognize(lex.tab_tokens.TK_TRUNCATABLE)
    return true
  elseif tab_follow.rule_272[token] then
    --empty
  end
end

rules.value_element_l = function ()
  if (tab_firsts.rule_285[token]) then
    rules.value_element()
    rules.value_element_l()
  elseif (tab_follow.rule_286[token]) then
    --empty
  end
end

rules.value_element = function ()
  if (tab_firsts.rule_287[token]) then
    rules.export()
  elseif (tab_firsts.rule_288[token]) then
    rules.state_member()
  elseif (tab_firsts.rule_289[token]) then
    rules.init_dcl()
  end
end

rules.state_member = function ()
  if (tab_firsts.rule_290[token]) then
    recognize(lex.tab_tokens.TK_PUBLIC)
    rules.state_member_tail("public")
  elseif (tab_firsts.rule_291[token]) then
    recognize(lex.tab_tokens.TK_PRIVATE)
    rules.state_member_tail("private")
  end
end

rules.state_member_tail = function (access)
  rules.declarator_l(rules.type_spec(), access)
  recognize(";")
end

rules.init_dcl = function ()
  if (tab_firsts.rule_292[token]) then
    recognize(lex.tab_tokens.TK_FACTORY)
    recognize(lex.tab_tokens.TK_ID)
    local name = getID()
    define(name, TAB_TYPEID.FACTORY)
    recognize("(")
    rules.init_param_dcls()
    recognize(")")
    rules.raises_expr_e()
    recognize(";")
    gotoFatherScope()
  end
end


---
-- EVENT DECLARATION
--------------------------------------------------------------------------

rules.eventtype_tail = function (name)
  if tab_firsts.rule_302[token] then
    define(name, TAB_TYPEID.EVENTTYPE)
    rules.value_inhe_spec()
    recognize("{")
    rules.value_element_l()
    recognize("}")
    local tab_eventtypescope = currentScope
    gotoFatherScope()
    return tab_eventtypescope
  elseif tab_firsts.rule_303[token] then
    define(name, TAB_TYPEID.EVENTTYPE)
    recognize("{")
    rules.value_element_l()
    recognize("}")
    local tab_eventtypescope = currentScope
    gotoFatherScope()
    return tab_eventtypescope
  elseif tab_follow.rule_304[token] then
    return dclForward(name, TAB_TYPEID.EVENTTYPE)
  end
end

--[[function type_prefix_dcl()
  if tab_firsts.rule_260[token] then
    recognize(lex.tab_tokens.TK_TYPEPREFIX)
    rules.scoped_name()
    recognize(lex.tab_tokens.TK_STRING_LITERAL)
  else
    sinError("'typeprefix'")
  end
end
]]


---
-- API
--------------------------------------------------------------------------

function parse(stridl, options)
  if not options then
    options = {}
  end

  if options.callbacks then
    callbacks = options.callbacks
    for type, tab in pairs(TAB_BASICTYPE) do
      local callback = callbacks[type]
      if callback then
        if (type == 'TYPECODE') then
        else
          TAB_BASICTYPE[type] = callback
        end
      end
    end

    for type, tab in pairs(TAB_IMPLICITTYPE) do
      local callback = callbacks[type]
      if callback then
        TAB_IMPLICITTYPE[type] = callback
      end
    end
  else
    callbacks = {}
  end

-- Estrutura que armazena o grafo de saída.
-- A tabela é inicializada com o escopo 'GLOBAL'.
  output                    = {absolute_name = ''}
  currentScope              = output

-- Estrutura que armazena informações pertinentes a cada identificador mapeado.
-- Auxilia o processo de geração do grafo de saída.
-- A tabela é indexada por *absolute name*.
  namespaces                = {[''] = {namespace = output}}
  forwardDeclarations       = {}
  idl                       = stridl
  CORBAVisible              = nil
  currentScopeName          = ''
  tab_identifiers           = {}
  scopeRoots                = {}
  table.insert(scopeRoots, {root = '', scope = ''})
  lex.init()
  token = getToken()
--Implicit definitions
--  CORBA::TypeCode
  if not options.notypecode then
    define('CORBA', TAB_TYPEID.MODULE)
    define('TypeCode', TAB_TYPEID.TYPECODE, TAB_IMPLICITTYPE.TYPECODE)
    gotoFatherScope()
  end
-- Starts parsing with the first grammar rule.
  rules.specification()
-- Removing CORBA::TypeCode implicit definition.
  if (not options.notypecode) and (not CORBAVisible) then
    table.remove(output, 1)
  end
  return output
end
