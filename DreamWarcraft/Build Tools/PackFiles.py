import xml.etree.ElementTree as ET
import checkmod

DEBUG = 0

if DEBUG:
    XMLPath     = '../../Package.xml'
    EmbedFile   = '../../DreamInstaller/Embed.inc'
    CodeFile    = '../../DreamInstaller/Files.inc'
else:
    XMLPath     = '../Package.xml'
    EmbedFile   = 'Embed.inc'
    CodeFile    = 'Files.inc'

def Init():    
    # XML Data
    root = ET.parse(XMLPath).getroot();
    f = open(EmbedFile, 'w')
    fc = open(CodeFile, 'w')
    i = 0
    for file in root:
        i = i + 1
        name = file.get('name')
        path = file.text
        f.write('%d\tRCDATA\t"%s"\n' % (i, path))
        fc.write('{L"%s", %d},\n' % (name, i));
    fc.close()
    f.close()
def Main():
    Init()

if __name__ == '__main__':
    if (not checkmod.check(XMLPath) and not DEBUG):
        print('PackFiles: No change on xml, skip.')
    else:
        Main()


