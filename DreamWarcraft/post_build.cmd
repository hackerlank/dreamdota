SET ROOT_PATH=%1
SET FILE_PATH=%2
SET OUT_PATH=%3
SET OUT_NAME=%4

"Build Tools\MPQFixEngine\MPQFixEngine.exe"

IF NOT EXIST "../LastBuildOutput/" mkdir "../LastBuildOutput/"

copy %FILE_PATH%/b + %ROOT_PATH%"Resource.mpq"/b "../LastBuildOutput/"%OUT_NAME% /Y

:END