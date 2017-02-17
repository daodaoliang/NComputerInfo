rmdir /S /Q %~dp0..\NComputerInfo\release
rmdir /S /Q %~dp0..\NComputerInfo\debug
rmdir /S /Q %~dp0..\NComputerInfo\build_
rmdir /S /Q %~dp0..\Example\build_
rmdir /S /Q %~dp0..\Example\release
rmdir /S /Q %~dp0..\Example\debug
rmdir /S /Q %~dp0..\bin
del /Q %~dp0..\Makefile*
del /Q %~dp0..\NComputerInfo\Makefile*
del /Q %~dp0..\Example\Makefile*
