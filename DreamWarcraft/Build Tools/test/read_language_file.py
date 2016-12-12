import array
import os

FileName = '../../Strings.xml'
Root = None
Lang = {}
StringID = {}
StringOffset = {}

def XOR(arr):
    #print("input size: " + str(len(arr)))
    #RSA public key
    f = open('../in/RSA_public_key.bin', 'rb')
    b = f.read(128)
    keyArr = array.array('L', b)
    f.close();    
    for i in range(0, len(arr)):
        old = arr[i]
        arr[i] ^= keyArr[i % 32]
        #print("old = " + hex(old) + " result = " + hex(arr[i]))

def GetArray(src, offset, size):
    rv = array.array('L')
    for i in range(0, size):
        rv[i] = src[i + offset]
    return rv    

if __name__ == '__main__':
    # Output Format
    # HEADER:
    #   dwTOTAL_ID | dwLength | dwLength .... | dwDATA_SIZE | DATA
    lang = input('lang ID: ')
    fileName = '../out/' + lang + '.bin'
    fileSize = os.path.getsize(fileName)
    print('file size(byte): ' + str(fileSize)) 
    dwordCount = fileSize / 4
    f = open(fileName, 'rb')
    arr = array.array('L')
    arr.fromfile(f, int(dwordCount))
    XOR(arr)
    
    
    p = print
    totalIdCount = arr[0]
    p('id count: ' + str(totalIdCount))
    for i in range(0, totalIdCount):
        p('[String ID %d] size = %d' % (i, arr[1 + i]))
    dataSize = arr[1 + totalIdCount]
    p('Data Size = %d' % dataSize)
