@echo off
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
msbuild -verbosity:minimal -t:Rebuild -p:Configuration="Debug" "D:/work/soul-mod/tools/otava/test/bound_temporary/memdbg/bound_temporary.vcxproj" > "D:/work/soul-mod/tools/otava/test/bound_temporary/memdbg/build.out.log" 2> "D:/work/soul-mod/tools/otava/test/bound_temporary/memdbg/build.error.log"
exit %ERRORLEVEL%
