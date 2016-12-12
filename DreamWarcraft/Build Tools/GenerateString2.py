import xml.etree.ElementTree as ET
import array
import sys
import os
import hashlib
import shutil

import checkmod

def to_bytes(n, length, endianess='big'):
    h = '%x' % n
    s = ('0'*(len(h) % 2) + h).zfill(length*2).decode('hex')
    return s if endianess == 'big' else s[::-1]

DEBUG = 0

CWD = os.getcwd()

if DEBUG:
    LocaleFilePath  = '../../Locales.xml'
    StringFilePath  = '../../Strings.xml'
    KeyFilePath     = 'in/RSA_public_key.bin'
    InitFile        = 'Locale.inc'
    DataFile        = 'LocaleData.inc'
    StringIdFile    = 'LocaleStringId.inc'
else:
    if CWD.find('DreamAuth') != -1:
        LocaleFilePath  = '../Locales.xml'
        StringFilePath  = '../Strings.xml'
        KeyFilePath     = '../DreamWarcraft/Build Tools/in/RSA_public_key.bin'
        InitFile        = 'Locale.inc'
        DataFile        = 'LocaleData.inc'
        StringIdFile    = 'LocaleStringId.inc'
    else:
        LocaleFilePath  = '../Locales.xml'
        StringFilePath  = '../Strings.xml'
        KeyFilePath     = './Build Tools/in/RSA_public_key.bin'
        InitFile        = '../DreamAuth2/Locale.inc'
        DataFile        = '../DreamAuth2/LocaleData.inc'
        StringIdFile    = '../DreamAuth2/LocaleStringId.inc'        

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
    out_code = ''
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
                    s += to_bytes(int(0), 1, sys.byteorder)
            l = len(s)
            outArr.append(offset)
            offset = offset + l
            dataArr += array.array('L', s)
        outArr.append(offset) #dwOffset last
        outArr.extend(dataArr)
        
        if not DEBUG:
            ArrayXOR(outArr)
        
        out_code += ('uint32_t LOCALE_DATA_%s[] = {' % lang.upper().replace('-', '_'));
        
        data_list = []
        for num in outArr:
            data_list.append('0x%08X' % num)        
        out_code += ','.join(data_list)

        out_code += '};\n' 
        
        print('Language id %s : %d bytes.' % (lang, len(outArr) * 4))
    
    # Output Locale data
    print('Saving locale data...')
    f = open(DataFile, 'w')
    f.write(out_code)
    f.close()

    # Output Supported Locales
    print('Saving locale list data...')
    f = open(InitFile, 'w')
    locale_code = ''
    for locale in ET.parse(LocaleFilePath).getroot():
        locale_code += ('DEFINE_LOCALE(%s, %u, "%s")\n' % (locale.get('id').upper().replace('-', '_'), int(locale.get('LCID')), locale.text))
    f.write(locale_code)
    f.close()

    # Output String Id
    print('Saving locale string id...')
    f = open(StringIdFile, 'w')
    f.write('namespace STR {\n')
    i = 0
    for sid in StringIdSet:
        f.write(('\tconst uint32_t %s = 0x%08X;\n' % (sid, i)))
        i = i + 1
    f.write('}\n')
    f.close()
#    if DEBUG:
#        DecryptorsGenerate()    

if __name__ == '__main__':
    if (not DEBUG and not checkmod.check(StringFilePath) and not checkmod.check(LocaleFilePath)):
        print('GenerateString: No change, skip.')
    else:
        Main()

    
