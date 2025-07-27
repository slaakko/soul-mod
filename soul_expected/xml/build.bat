@echo off
pushd xml_parser_expected
call build.bat
popd
pushd xpath_expected
call build.bat
popd
