@echo off
IF NOT EXIST ucd.all.flat.xml powershell -command "Expand-Archive -Force '%~dp0ucd.all.flat.zip' '%~dp0'"
IF NOT EXIST soul_ucd.bin make_soul_ucd
