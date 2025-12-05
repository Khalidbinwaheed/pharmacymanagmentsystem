@echo off
cd /d d:\Github\pharmacymanagmentsystem
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Auxiliary\Build\vcvars64.bat"
cl.exe /EHsc pharmacy_system.cpp
if %ERRORLEVEL% EQU 0 (
    echo.
    echo Running program...
    pharmacy_system.exe
) else (
    echo Compilation failed
)
pause
