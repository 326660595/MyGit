# 
# # 1 . 获得shell脚本所在的绝对路径
# 
# ##################################

#!/bin/bash

# CURRENT_DIR=$(cd $(dirname $0); pwd)

# 或者

# CURRENT_DIR=$(cd `dirname $0`; pwd)

CURRENT_DIR=$(cd $(dirname $0); pwd)
#echo $0,打印文件名
echo $0
#打印文件所在绝对路径
echo $CURRENT_DIR

#在shell脚本所在路径，创建build文件夹
mkdir $CURRENT_DIR/build

#进入build文件夹
cd $CURRENT_DIR/build

#在build文件夹创建good文件
touch good
