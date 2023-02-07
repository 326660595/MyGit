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
