#!/bin/bash
###
 # @Author: russell 61924193+326660595@users.noreply.github.com
 # @Date: 2025-05-08 11:18:20
 # @LastEditors: russell 61924193+326660595@users.noreply.github.com
 # @LastEditTime: 2025-05-08 11:23:18
 # @FilePath: /MyGit/shell/losetup-remove.sh
 # @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
### 


IMGLOOP="$1"

sudo umount /mnt/sdcard1  # 卸载第一个分区
sudo umount /mnt/sdcard2  # 卸载第二个分区

sudo losetup -d $IMGLOOP

