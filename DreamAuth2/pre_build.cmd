SET ROOT_PATH=%1
SET FILE_PATH=%2
SET OUT_PATH=%3
SET OUT_NAME=%4

echo Generating Resource String...
"..\DreamWarcraft\Build Tools\GenerateResString.py"
echo Generating Locale String...
"..\DreamWarcraft\Build Tools\GenerateString2.py"

:END