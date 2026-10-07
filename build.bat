@echo off
setlocal enabledelayedexpansion

echo ==============================================
echo   Building File-Based Notes Saver for Windows
echo ==============================================

where g++ >nul 2>nul
if %errorlevel% equ 0 (
    echo [Compiler] Detected MinGW / GCC (g++)
    echo Compiling source files...
    g++ -std=c++17 -Wall -Wextra -Iinclude src\Utils.cpp src\Note.cpp src\FileManager.cpp src\InputValidator.cpp src\SearchEngine.cpp src\NoteSorter.cpp src\BackupManager.cpp src\NoteManager.cpp src\UI.cpp src\main.cpp -o notes_saver.exe
    if %errorlevel% equ 0 (
        echo [SUCCESS] Build succeeded: notes_saver.exe created!
        echo Run notes_saver.exe or run.bat to start.
    ) else (
        echo [ERROR] Compilation failed.
    )
    goto end
)

where cl >nul 2>nul
if %errorlevel% equ 0 (
    echo [Compiler] Detected Microsoft Visual C++ (MSVC cl.exe)
    echo Compiling source files...
    cl /EHsc /std:c++17 /Iinclude src\*.cpp /Fe:notes_saver.exe
    if %errorlevel% equ 0 (
        echo [SUCCESS] Build succeeded: notes_saver.exe created!
        echo Run notes_saver.exe or run.bat to start.
    ) else (
        echo [ERROR] Compilation failed.
    )
    goto end
)

where cmake >nul 2>nul
if %errorlevel% equ 0 (
    echo [Compiler] Detected CMake. Configuring build directory...
    cmake -B build
    cmake --build build --config Release
    if %errorlevel% equ 0 (
        copy build\Release\notes_saver.exe notes_saver.exe >nul 2>nul
        if not exist notes_saver.exe (
            copy build\notes_saver.exe notes_saver.exe >nul 2>nul
        )
        echo [SUCCESS] Build succeeded: notes_saver.exe created!
        goto end
    )
)

echo [ERROR] No supported C++ compiler found (g++, cl, or cmake).
echo Please install one of the following:
echo   1. MinGW-w64 (via MSYS2, WinLibs, or Chocolatey: choco install mingw)
echo   2. Visual Studio Community with "Desktop development with C++"
echo   3. Or run using WSL (Windows Subsystem for Linux).

:end
endlocal
