import array
import re
import os

import checkmod

DefFilePath     = 'Offsets.def'
OutputPath      = 'Build Tools/out/%s.bin'

Lines = []
Data = {}
Versions = []

def Main():    
    f = open(DefFilePath, 'r')
    c = f.readlines()
    f.close()
    
    #Cleanup
    for line in c:
        line = re.sub('Offset Table', '', line)
        line = re.sub('\/\/.+', '', line)
        line = re.sub('^\s+', '', line)
        line = re.sub('\s+', '|', line)
        if len(line) > 1:
            Lines.append(line)

    f = open('test.txt', 'w')
    f.writelines('\n'.join(Lines))
    f.close()
    
    #Parse
    for ver in Lines[0].split('|'):
        if ver:
            Versions.append(ver)
            Data[ver] = []
            
    for i in range(1, len(Lines)):
        line_elements = Lines[i].split('|')
        for ioffset in range(1, len(line_elements) - 1):
            offset = line_elements[ioffset]
            Data[Versions[ioffset-1]].append(offset)

    for ver in Data:
        f = open(OutputPath % ver, 'wb')
        out = array.array('L')
        for offset in Data[ver]:
            out.append(int(offset, 16))
        f.write(out)
        f.close()

    os.system('cscript //NoLogo "Build Tools/GenerateOffsets.js"')

if __name__ == '__main__':
    if checkmod.check(DefFilePath):
        Main()
    else:
        print("Offset not changed, skip.")    
