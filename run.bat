@echo off
if not exist notes_saver.exe (
    echo notes_saver.exe not found. Running build.bat first...
    call build.bat
)

if exist notes_saver.exe (
    cls
    notes_saver.exe
) else (
    echo [ERROR] Could not build or find notes_saver.exe.
    pause
)
