@echo off
IF NOT EXIST snginst.exe xcopy /Y /D ..\x64\Release\snginst.exe .
IF NOT EXIST snglexer.dll xcopy /Y /D ..\x64\Release\snglexer.dll .
IF NOT EXIST sngrex.dll xcopy /Y /D ..\x64\Release\sngrex.dll .
IF NOT EXIST sngutil.dll xcopy /Y /D ..\x64\Release\sngutil.dll .
IF NOT EXIST ..\bin mkdir ..\bin
IF NOT EXIST ..\lib mkdir ..\lib
snginst -v ..\x64\Debug\*.exe ..\bin
snginst -v ..\x64\Release\*.exe ..\bin
snginst -v ..\x64\Debug\*.lib ..\lib
snginst -v ..\x64\Release\*.lib ..\lib