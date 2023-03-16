@echo off
SETLOCAL EnableDelayedExpansion
REM This removes the drinol dll
echo THIS WILL ONLY WORK IF YOU HAVE MCC INSTALLED!

echo Uninstalling drinol....

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

if exist "%MCCPATH%umpdc.dll" (
del /f "%MCCPATH%umpdc.dll"
rmdir /s /q "%MCCPATH%Drinol"
 echo Drinol has been uninstalled!
) else (
    echo Drinol has not been installed. There is nothing to delete.
)

pause