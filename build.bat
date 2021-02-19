@call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"

@echo off

@RD /S /Q build

mkdir build
pushd build
@cl -Zi /Febuild.exe %~dp0\source\winmain.c user32.lib gdi32.lib
popd

start "" %~dp0\build\build.exe