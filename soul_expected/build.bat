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
pushd slg_expected
call build.bat
popd
pushd spg_expected
call build.bat
popd
