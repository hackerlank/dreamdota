import xml.etree.ElementTree as ET
import array
import sys
import os
import hashlib
import shutil
import re

import checkmod

DEBUG = 0

ProjectName = 'DreamAuth2'

Locales = {'en-us':0x409, 'zh-cn':0x804, 'pt-pt':0x816, 'ru-ru':0x419}

StringIdFormat = 'const int %s = %d;\n'
StringFormat = 'StringMap[%u][%d] = L"%s";\n'

if DEBUG:
    StringFilePath  = '../../ResStrings.xml'
    HeaderPath      = '../../' + ProjectName + '/ResStringId.inc'
    CodePath        = '../../' + ProjectName + '/ResString.inc'
else:
    StringFilePath  = '../ResStrings.xml'
    HeaderPath      = 'ResStringId.inc'
    CodePath        = 'ResString.inc'

DefaultLanguage = 'en-us'
KeyArray        = array.array('L')
LanguageSet     = set()
StringData      = {}
StringIdSet     = set()

def Init():    
    # XML Data
    root = ET.parse(StringFilePath).getroot();
    for string in root:
        sid = string.get('id')
        StringIdSet.add(sid)
        for value in string:
            lang = value.get('lang')
            LanguageSet.add(lang)
            if StringData.get(lang) == None:
                StringData[lang] = {}                
            StringData[lang][sid] = value.text

def SaveId():
    f = open(HeaderPath, 'w', -1, 'utf-16')
    i = 0
    for sid in StringIdSet:
        i = i + 1
        f.write(StringIdFormat % (sid, i))
    f.close()
 
def SaveString():
    f = open(CodePath, 'w', -1, 'utf-16')
    for lang in LanguageSet:
        i = 0
        for sid in StringIdSet:
            i = i + 1
            f.write(StringFormat % (int(Locales[lang]), i, (StringData[lang][sid]).replace('\"', '\\"')))
    f.close()

def Main():
    Init()
    SaveId()
    SaveString()

if __name__ == '__main__':
    if (not checkmod.check(StringFilePath)):
        print('GenerateResString: No change on xml, skip.')
    else:
        Main()


