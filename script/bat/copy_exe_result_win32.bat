set SRC_EXE_DIR=%1
set SRC_EXE_NAME=%2

IF NOT EXIST ..\..\..\..\bin\win32\%SRC_EXE_DIR% md ..\..\..\..\bin\win32\%SRC_EXE_DIR%

copy /Y .\%SRC_EXE_DIR%\%SRC_EXE_NAME% ..\..\..\..\bin\win32\%SRC_EXE_DIR%\%SRC_EXE_NAME%