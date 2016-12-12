import os
import hashlib

def check(FilePath):
    CacheFileName = FilePath + '.md5'
    rv = False
    cache_exist = os.path.exists(CacheFileName)
    if cache_exist:
         size = os.path.getsize(CacheFileName)
         f = open(CacheFileName, 'rb')
         c = f.read(size)
         f.close()
         cachehash = c
    size = os.path.getsize(FilePath)
    f = open(FilePath, 'rb')
    c = f.read(size)
    f.close()   
    md5 = hashlib.md5()
    md5.update(c)
    filehash = md5.digest()
    f = open(CacheFileName, 'wb')
    f.write(filehash)
    f.close()
    return not cache_exist or cachehash != filehash
