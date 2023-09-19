@echo off

REM 定义一个名为 MyFunction 的伪函数
:MyFunction
echo this MyFunction 
echo num :%1
echo num :%2
echo.
goto :eof

REM 主程序
echo start

REM 调用 MyFunction 函数，并传递两个参数
call :MyFunction 1 2

echo end

REM 结束脚本
exit /b 0
