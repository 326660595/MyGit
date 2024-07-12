@REM pyinstaller -F -w -i ..\tool\bluetooth.ico .\auto_fun.py

@REM pyinstaller -F -i ..\tool\bluetooth.ico .\test_creat_exe.py
pyinstaller -F .\open_close_ble.py
@REM pyinstaller -F -i ..\tool\small_yellow_peple.ico .\auto_fun.py

@REM 根据你提供的打包设置，使用了 PyInstaller 工具将 Python 文件 test_creat_exe.py 打包为单个可执行文件。选项 -F 表示生成单个可执行文件，-w 表示以无窗口模式（无命令行窗口）运行。

@REM 由于使用了 -w 选项，该可执行文件将在后台静默运行，没有显示的执行窗口。这是预期的行为，和你的打包设置一致。

@REM 如果你希望显示一个执行窗口，请尝试移除 -w 选项，如下所示：
@REM -i：这个选项用于指定自定义图标文件。在这个例子中，.表示当前目录，所以.\esay_auto_update.py是图标文件的路径。

@REM pyinstaller -F -i ..\tool\bluetooth.ico .\test_creat_exe.py
