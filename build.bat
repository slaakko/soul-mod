@echo off
pushd examples\minilang
call build.bat
popd
pushd soul\common
call build.bat
popd
pushd soul\cpp
call build.bat
popd
pushd soul\lex
call build.bat
popd
pushd soul\re
call build.bat
popd
pushd soul\rex
call build.bat
popd
pushd soul\slg
call build.bat
popd
pushd soul\spg
call build.bat
popd
pushd soul\token
call build.bat
popd
pushd soul\xml\serialization
call build.bat
popd
pushd soul\xml\xml_parser
call build.bat
popd
pushd soul\xml\xpath
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
pushd test
call build.bat
popd
