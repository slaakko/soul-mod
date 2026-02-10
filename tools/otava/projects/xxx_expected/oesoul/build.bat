@echo off
pushd otoken
call build.bat
popd
pushd olex
call build.bat
popd
pushd ore
call build.bat
popd
pushd ocommon
call build.bat
popd
pushd ocpp
call build.bat
popd
pushd oslg
call build.bat
popd
pushd ospg
call build.bat
popd
