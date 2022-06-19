# Makefile for soul projects

# Run with nmake from Visual Studio 2022 x64 Native Tools Command Prompt

all: makedirs ext soul install unicode
	echo make succeeded.

makedirs:
	makedirs.bat

ext:
	cd ..\ext\zlib-1.2.11\contrib\masmx64 && bld_ml64.bat
	
soul:
	MSBuild -m -verbosity:minimal ..\soul.sln -p:Configuration="Debug"
	MSBuild -m -verbosity:minimal ..\soul.sln -p:Configuration="Release"

install:
	cd ..\inst && inst.bat

unicode:
	cd ..\unicode && build.bat
