@echo off

pushd %~dp0\..\
call Programs\Premake\premake5.exe --file=Starlight.lua gmake2
call Programs\Premake\premake5.exe --file=Starlight.lua vscode
popd
PAUSE