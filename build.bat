@echo off
pushd examples\minilang
call build.bat
popd
pushd soul
call build.bat
popd
pushd tools\otava\lexer
call build.bat
popd
pushd tools\otava\parser
call build.bat
popd
pushd tools\otava\build
call build.bat
popd
pushd tools\cpp2html
call build.bat
popd
pushd tools\slines
call build.bat
popd
pushd tools\soul2html
call build.bat
popd

