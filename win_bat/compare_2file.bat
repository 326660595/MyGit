@REM 要比较两个 .hex 文件是否相同，你可以使用文件比较工具或编程语言来实现。

@REM 一种简单的方法是使用 Python 编程语言。你可以使用以下代码来比较两个 .hex 文件的内容是否相同：

@REM python

@REM def compare_hex_files(file1, file2):
@REM     with open(file1, 'r') as f1, open(file2, 'r') as f2:
@REM         if f1.read() == f2.read():
@REM             print("Files are the same.")
@REM         else:
@REM             print("Files are different.")

@REM compare_hex_files("file1.hex", "file2.hex")

@REM 在这个示例中，我们定义了一个 compare_hex_files 函数，它接受两个文件路径作为参数。函数打开并逐行读取这两个文件的内容，然后比较它们是否相同。如果内容相同，则输出 "Files are the same."，否则输出 "Files are different."。

@REM 你可以将 "file1.hex" 和 "file2.hex" 替换为你要比较的两个 .hex 文件的路径。

fc NovaX_P.hex 1NovaX_P.hex > nul 2>&1

if errorlevel 1 (
    echo Files are different.
    exit /b 1
) else (
    echo Files are the same.
    exit /b 0
)