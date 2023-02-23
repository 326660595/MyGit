#!/bin/bash


echo "检查文件是否存在"

FILE=/etc/resolv.conf
if test -f "$FILE"; then
    echo "$FILE exist"
fi

FILE=/etc/resolv.russell
if test -f "$FILE"; then
    echo "$FILE exist"
else
    echo "不存在"
fi


FILE=/etc/resolv.conf
if [ -f "$FILE" ]; then
    echo "$FILE exist"
fi
FILE=/etc/resolv.conf
if [[ -f "$FILE" ]]; then
    echo "$FILE exist"
fi

num1=100
num2=100
if test $[num1] -eq $[num2]
then
    echo '两个数相等！'
else
    echo '两个数不相等！'
fi

# shell 语言中的 if 条件判断
# https://xiaojin21cen.blog.csdn.net/article/details/124015943

# 1、if 的基本语法:
# if [ command ];then
#    符合该条件执行的语句
# elif [ command ];then
#    符合该条件执行的语句
# else
#    符合该条件执行的语句
# fi

# 2、字符串的判断

# 字符串批较时，变量一定要用 双引号。
# [ -z "str" ] 如果str的长度为零，则为真 ，即判断是否为空，空即是真；
# [ -n "str" ] 如果str的长度非零，则为真 ，即判断是否为非空，非空即是真；
# [ "str1" = "str2" ] 如果两个字符串相同，则为真；
# [ "str1" != "str2" ] 如果字符串不相同，则为真；
# [ "str1" ]　 如果字符串不为空，则为真，与-n类似。


# 3\数值的判断

# 数值的比较千万不要使用大于号、小于号，数值的比较只能使用 -eq 、-gt 等。
# [ num1 -eq num2 ]      num1 和 num2 两数相等为真 , =
# [ num1 -ne num2 ]      num1 和 num2 两数不等为真 ,!=
# [ num1 -gt num2 ]      num1 大于 num1 为真 , >
# [ num1 -ge num2 ]      num1 大于等于num2 为真, >=
# [ num1 -lt num2 ]      num1 小于n um2 为真 , <
# [ num1 -le num2 ]      num1 小于等于 num2 为真, <=


# 4.文件和目录的判断


# [ -e file ] 如果 file 存在，则为真。
# [ -d DIR ]  如果 file 存在，且是一个目录，则为真。
# [ -f file ] 如果 file 存在，且是一个普通文件，则为真。

# [ -r file ] 如果 file 存在且是可读的，则为真。
# [ -w file ] 如果 file存在且是可写的，则为真。
# [ -x file ] 如果 file 存在且是可执行的，则为真。

# [ -b file ] 如果 file 存在，且是一个块特殊文件，则为真。
# [ -c file ] 如果 file 存在，且是一个字特殊文件，则为真。


# [ -g file ] 如果 file 存在且已经设置了SGID，则为真。
# [ -k file ] 如果 file 存在且已经设置了粘制位，则为真。
# [ -p file ] 如果 file 存在且是一个名字管道(F如果O)，则为真。


# [ -s file ] 如果 file 存在且大小不为0，则为真。
# [ -t FD ] 如果文件描述符 FD 打开且指向一个终端，则为真。
# [ -u file ] 如果 file 存在且设置了SUID (set user ID)，则为真。

# [ -O file ] 如果 file 存在且属有效用户ID，则为真。
# [ -G file ] 如果 file 存在且属有效用户组，则为真。
# [ -L file ] 如果 file 存在且是一个符号连接，则为真。
# [ -N file ] 如果 file 存在 and has been mod，如果ied since it was last read则为真。
# [ -S file ] 如果 file 存在且是一个套接字，则为真。
# [ file1 -ot file2 ] 如果 file1 比 file2 要老, 或者 file2 存在且 file1 不存，在则为真。
# [ file1 -ef file2 ] 如果 file1 和 file2 指向相同的设备和节点号，则为真。
