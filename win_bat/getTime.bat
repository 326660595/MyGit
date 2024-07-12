@echo off
setlocal

REM 获取当前日期
for /f "tokens=1-3 delims=/ " %%a in ('date /t') do (
    set "year=%%a"
    set "month=%%b"
    set "day=%%c"
)

for /f "tokens=1-4 delims=/: " %%a in ('time /t') do (
    set "hour=%%a"
    set "minute=%%b"
    @REM set "second=%%c"
)

echo %year%
echo %month%
echo %day%

echo %hour%
echo %minute%
@REM echo %second%

REM 生成文件名
set "filename=%year%-%month%%day%-%hour%%minute%.txt"

echo %filename%

echo "firmware creat" > %filename%

endlocal
