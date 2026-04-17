@echo off
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
msbuild -verbosity:minimal -t:Rebuild -p:Configuration="Debug" "D:/work/soul-mod/tools/otava/test/map/memdbg/map.vcxproj" > "D:/work/soul-mod/tools/otava/test/map/memdbg/build.out.log" 2> "D:/work/soul-mod/tools/otava/test/map/memdbg/build.error.log"
exit %ERRORLEVEL%
