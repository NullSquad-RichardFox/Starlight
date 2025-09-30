@echo off

pushd %~dp0\..\
call Programs\Premake\premake5.exe --file=Nebula.lua gmake2
popd
PAUSE