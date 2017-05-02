set LIB_VERSION=%1
set AIM_LIB_NAME=%2

IF NOT EXIST ..\..\..\..\lib\win32\%LIB_VERSION% md ..\..\..\..\lib\win32\%LIB_VERSION%

copy /Y .\%LIB_VERSION%\%AIM_LIB_NAME% ..\..\..\..\lib\win32\%LIB_VERSION%\%AIM_LIB_NAME%