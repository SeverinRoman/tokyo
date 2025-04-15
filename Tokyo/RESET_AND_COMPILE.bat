@echo off
setlocal enabledelayedexpansion

rem Change this to the path to your Unreal Engine's "UnrealVersionSelector.exe"
set "UEVersionSelector=C:\Program Files (x86)\Epic Games\Launcher\Engine\Binaries\Win64\UnrealVersionSelector.exe"

rem Change this to the path to your UnrealBuildTool
set "UnrealBuildTool=C:\Program Files\Epic Games\UE_5.5\Engine\Binaries\DotNET\UnrealBuildTool\UnrealBuildTool.exe"

rem Get the directory of the batch file
set "BatchFileDir=%~dp0"

rem Find the .uproject file in the batch file directory
for %%i in ("%BatchFileDir%*.uproject") do set "UProjectFile=%%i"

rem Find the .sln file in the batch file directory
for %%i in ("%BatchFileDir%*.sln") do set "SolutionFile=%%i"

if not defined UProjectFile (
    echo .uproject file not found in the batch file directory.
    pause
    exit /b
)

rem Extract the project name from the .uproject file
for /f "usebackq tokens=2,* delims=:" %%a in ("!UProjectFile!") do (
    set "ProjectName=%%~b"
    set "ProjectName=!ProjectName:^"=!"
    set "ProjectName=!ProjectName: =!"
)

echo Cleaning project files...

rem Remove the Visual Studio solution file if it exists
if exist "!SolutionFile!" (
    del "!SolutionFile!"
    echo Deleted "!SolutionFile!"
) else (
    echo "!SolutionFile!" not found. Skipping deletion.
)

rem Remove Intermediate and Saved folders if they exist without confirmation prompt
rmdir /s /q "!BatchFileDir!Intermediate" 2>nul
rem rmdir /s /q "!BatchFileDir!Saved" 2>nul

rem Remove the additional files and folders
rmdir /s /q "!BatchFileDir!.vs" 2>nul
del /q "!BatchFileDir!.vsconfig" 2>nul
rmdir /s /q "!BatchFileDir!Binaries" 2>nul
rmdir /s /q "!BatchFileDir!Build" 2>nul
rmdir /s /q "!BatchFileDir!DerivedDataCache" 2>nul

echo Cleaning completed.

echo Generating project files...

rem Generate project files using UnrealVersionSelector
"%UEVersionSelector%" -projectfiles "!UProjectFile!"

echo Generating Visual Studio project files...

rem Generate Visual Studio project files using UnrealBuildTool
"%UnrealBuildTool%" Development Win64 -Project="!UProjectFile!" -TargetType=Editor

echo Generation completed.

echo Run .uproject.
@REM start "BatchFileDir=%~dp0" "!UProjectFile!"

echo Run .sln
@REM start "BatchFileDir=%~dp0" "!SolutionFile!"

rem Pause the script so you can see the output before it closes
pause