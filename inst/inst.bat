@echo off
IF NOT EXIST soul_inst.exe xcopy /Y /D ..\x64\Release\soul_inst.exe .
IF NOT EXIST ..\bin mkdir ..\bin
IF NOT EXIST ..\lib mkdir ..\lib
IF NOT EXIST ..\rc mkdir ..\rc
soul_inst -v ..\x64\Debug\*.exe ..\bin
soul_inst -v ..\x64\Release\*.exe ..\bin
soul_inst -v ..\x64\Debug\*.lib ..\lib
soul_inst -v ..\x64\Release\*.lib ..\lib
soul_inst -v ..\soul\lex\*.classmap.compressed ..\rc
soul_inst -v ..\soul\lex\*.classmap.rc ..\rc
soul_inst -v ..\soul\rex\*.classmap.compressed ..\rc
soul_inst -v ..\soul\rex\*.classmap.rc ..\rc
soul_inst -v ..\soul\xml\xpath\*.classmap.compressed ..\rc
soul_inst -v ..\soul\xml\xpath\*.classmap.rc ..\rc
soul_inst -v ..\soul\xml\serialization\*.classmap.compressed ..\rc
soul_inst -v ..\soul\xml\serialization\*.classmap.rc ..\rc
soul_inst -v ..\tools\otava\projects\soul\oslg\release\2\oslg.exe ..\bin
soul_inst -v ..\tools\otava\projects\soul\ospg\release\2\ospg.exe ..\bin
soul_inst -v ..\tools\otava\projects\xxx_expected\oesoul\oeslg\release\2\oeslg.exe ..\bin
soul_inst -v ..\tools\otava\projects\xxx_expected\oesoul\oespg\release\2\oespg.exe ..\bin
soul_inst -v ..\tools\otava\projects\xxx_expected\oexml\oexml_stats\release\2\oexml_stats.exe ..\bin
soul_inst -v ..\tools\otava\projects\xxx_expected\oexml\oexpath_test\release\2\oexpath_test.exe ..\bin
soul_inst -v ..\tools\otava\projects\xxx_expected\oecompiler\oec\release\2\oec.exe ..\bin
