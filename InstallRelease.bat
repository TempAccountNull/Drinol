@echo off
SETLOCAL EnableDelayedExpansion
REM This puts the drinol dll into your mcc binaries directory and renames it so that mcc loads it on startup.
echo THIS WILL ONLY WORK IF YOU HAVE MCC INSTALLED!

echo Installing drinol....

REM Get the path of steams config folder containing libraryfolders.vdf
FOR /F "tokens=2* skip=2" %%a in ('reg query "HKLM\SOFTWARE\WOW6432Node\Valve\Steam" /v "InstallPath"') do set SteamPath=%%b

set SteamConfig="%SteamPath%\config"

cd /d %SteamConfig%


REM Search libraryfolders.vdf to see if mcc is installed and output the result into a variable
(for /F "delims=" %%G in ('findstr /C:"path" libraryfolders.vdf') do (

REM Get paths of the steam library locations.
set x=%%G

REM Skip past first 10 characters as they are useless
set x=!x:~10!

REM Remove all quotes
set x=!x:"=!

REM Remove double backslashes
set x=!x:\\=\!

set MCCBinariesLocation=!x!\steamapps\common\Halo The Master Chief Collection\mcc\binaries\win64\

if exist !MCCBinariesLocation! (
    rem path exists
    set MCCPATH=!MCCBinariesLocation!
)

) )

if exist %~dp0\x64\Release\Drinol.dll (
    rem file exists
    cd /d %~dp0\x64\Release
    echo f | xcopy "Drinol.dll" "%MCCPATH%umpdc.dll" /q /Y
    echo Drinol has been installed!
) else (
    echo The release binaries of Drinol could not be found.
)

pause