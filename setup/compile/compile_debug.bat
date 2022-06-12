call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
msbuild -verbosity:minimal -t:Rebuild -p:Configuration="Debug" "C:\work\soul-mod\setup\program\setup.vcxproj" > "C:\work\soul-mod\setup\compile\debug_stdout.txt" 2> "C:\work\soul-mod\setup\compile\debug_stderr.txt"
