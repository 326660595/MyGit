#!/bin/bash
###
 # @Author: russell 61924193+326660595@users.noreply.github.com
 # @Date: 2025-05-08 11:18:03
 # @LastEditors: russell 61924193+326660595@users.noreply.github.com
 # @LastEditTime: 2025-05-08 13:47:47
 # @FilePath: /MyGit/shell/losetup-add.sh
 # @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
### 
#russell:挂载镜像为loop设备

IMG="$1"

sudo losetup -f --show -P $IMG

sudo mkdir /mnt/sdcard1 /mnt/sdcard2  # 创建挂载点目录
# sudo mount /dev/loop0p1 /mnt/sdcard1  # 挂载第一个分区
# sudo mount /dev/loop0p2 /mnt/sdcard2  # 挂载第二个分区