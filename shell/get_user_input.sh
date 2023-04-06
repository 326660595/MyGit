#!/bin/bash
# author:菜鸟教程
# url:www.runoob.com

echo "Shell 传递参数实例！"
echo "执行的文件名：$0"
echo "第一个参数为：$1"
echo "第二个参数为：$2"
echo "第三个参数为：$3"

all="all"

if [ $3 = $all ]; then
    echo "相等"
else
    echo "不相等"
fi

var1="hello"
var2="world"
if [ $var1 = $var2 ]; then
    echo "$var1 < $var2"
# 在shell中>或<是输入或输出重定向符号，需要加反斜杠作转义
elif [ $var1 \< $var2 ]; then
    echo "$var1 < $var2"
else
    echo "$var1 > $var2"
fi
