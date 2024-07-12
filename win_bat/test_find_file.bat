@REM # Verify built files
@REM if [[ -e  test_file.txt]]; then
@REM     echo "Build successufull!"
@REM     true
@REM else
@REM     echo "Build failed!"
@REM     false
@REM fi

@echo off

@REM REM Verify built files
if exist test_file.txt (
    if exist test_file1.txt 
    echo Build successful!
    exit /b 0
)

echo Build failed!
exit /b 1

if exist test_file.txt (
    if exist test_file1.txt (
        echo Build successful!
        exit /b 0
    )
)