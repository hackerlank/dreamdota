import xml.etree.ElementTree as ET
import array
import sys
import os
import hashlib
import shutil

import checkmod

DEBUG = 0

if DEBUG:
    StringFilePath  = '../../Strings.xml'
    KeyFilePath     = 'in/RSA_public_key.bin'
    OutputPath      = 'out/%s'
    IdHeaderPath    = 'StringId.h'
else:
    StringFilePath  = '../Strings.xml'
    KeyFilePath     = 'Build Tools/in/RSA_public_key.bin'
    OutputPath      = 'Language/%s.bin'
    IdHeaderPath    = 'StringId.h'

DefaultLanguage = 'en-us'
KeyArray        = array.array('L')
LanguageSet     = set()
StringData      = {}
StringIdSet     = set()

def Init():
    # KEY
    f = open(KeyFilePath, 'rb')
    KeyArray.fromfile(f, 32)
    f.close()
    
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

def ArrayXOR(arr):
    for i in range(0, len(arr)):
        old = arr[i]
        arr[i] ^= KeyArray[i % 32]


def DecryptorsGenerate():
    f = open(KeyFilePath, 'rb')
    b = f.read(128)
    keyArr = array.array('L', b)
    f.close();
    for i in range(0, 32):
        print('REGISTER_DECRYPTOR(%d, %s);' % (i, hex(keyArr[i])))

def Main():
    Init()
    #   dwTOTAL_ID | dwOffset | dwOffset .... | DATA 
    stringTotal = len(StringIdSet)
    for lang in LanguageSet:      
        offset = 0
        outArr = array.array('L')
        dataArr = array.array('L')
        outArr.append(stringTotal) # dwTOTAL_ID
        for sid in StringIdSet:
            if sid in StringData[lang]:
                s = StringData[lang][sid].encode('utf-8')
            else:
                s = StringData[DefaultLanguage][sid].encode('utf-8')
            l = len(s)
            if l % 4:
                for i in range(0, 4 - (l % 4)):
                    s += int(0).to_bytes(1, sys.byteorder)
            l = len(s)
            outArr.append(offset)
            offset = offset + l
            dataArr += array.array('L', s)
        outArr.append(offset) #dwOffset last
        outArr.extend(dataArr)
        f = open(OutputPath % lang, 'wb')
        if not DEBUG:
            ArrayXOR(outArr)
        outArr.tofile(f)
        f.close()
        print('Language id %s : %d bytes written.' % (lang, len(outArr)))

        f = open(IdHeaderPath, 'w')
        f.write('namespace STR {\n')
        i = 0
        for sid in StringIdSet:
            f.write(('\tconst uint32_t %s = 0x%08X;\n' % (sid, i)))
            i = i + 1
        f.write('}\n')
        f.close()
    if DEBUG:
        DecryptorsGenerate()    

if __name__ == '__main__':
    if (not DEBUG and not checkmod.check(StringFilePath)):
        print('GenerateString: No change on xml, skip.')
    else:
        Main()

    
