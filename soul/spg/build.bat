@echo off
pushd ..\cpp
call build.bat
popd
pushd ..\common
call build.bat
popd
spg -v spg_parsers.spg
