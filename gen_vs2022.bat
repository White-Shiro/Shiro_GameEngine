@REM #change current directory to this file
@%~d0
@cd %~dp0

cmake -G "Visual Studio 17 2022"  -B build/ShiroGameEngine-x64-windows .

@pause