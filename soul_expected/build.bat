@echo off
pushd token_expected
call build.bat
popd
pushd common_expected
call build.bat
popd
pushd cpp_expected
call build.bat
popd
pushd lex_expected
call build.bat
popd
pushd re_expected
call build.bat
popd
pushd rex_expected
call build.bat
popd
pushd eslg
call build.bat
popd
pushd espg
call build.bat
popd
pushd xml
call build.bat
popd xml
