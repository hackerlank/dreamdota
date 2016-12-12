SET ROOT_PATH=%1
SET FILE_PATH=%2
SET OUT_PATH=%3
SET OUT_NAME=%4

cd %ROOT_PATH%

copy %FILE_PATH% "../Library/lib/%OUT_NAME%" /Y
copy %ROOT_PATH%"/*.h" "../Library/include/SimpleUI/" /Y

:END