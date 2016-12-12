SET ROOT_PATH=%1
SET FILE_PATH=%2

cd %ROOT_PATH%

echo Generating offsets...
"Build Tools\GenerateOffsets.py"

echo Packing strings...
"Build Tools\GenerateString2.py"

echo "Generating Revision info..."
SubWCRev.exe . SVN_info_raw.h SVN_info.h

:END