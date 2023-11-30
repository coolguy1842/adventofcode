@echo off

if "%1" == "" goto noyear
if "%2" == "" goto noday

.\aoc.exe d -y %1 -d %2 -I -i %1/input/day%2 -s session-cookie

goto exit

:noyear
echo you must specify the year
goto exit
:noday
echo you must specify the day
goto exit

:exit