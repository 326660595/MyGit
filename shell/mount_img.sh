
#russell:通过脚本打开挂载.img文件, 进行查看和修改。
#调用例子：/home/russell/work/MyGit/shell/check_img.sh ./Orangepi5plus_1.2.0_debian_bullseye_server_linux5.10.160.img



# 好的！以下是一个简单的 **自动脚本**，可以帮你：
###
 # @Author: russell 61924193+326660595@users.noreply.github.com
 # @Date: 2025-05-01 18:08:04
 # @LastEditors: russell 61924193+326660595@users.noreply.github.com
 # @LastEditTime: 2025-05-01 18:27:42
 # @FilePath: /MyGit/shell/check_img.sh
 # @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
### 

# 1. 自动读取 `.img` 镜像中的分区信息  
# 2. 自动计算偏移  
# 3. 自动挂载每个分区到 `/mnt/img1`, `/mnt/img2`, …  
# 4. 自动提示每个挂载点对应的分区类型和大小

# ---

# ## ✅ 脚本内容（建议保存为 `mount_img.sh`）：
# ```bash



#!/bin/bash

IMG="$1"

if [ -z "$IMG" ] || [ ! -f "$IMG" ]; then
    echo "Usage: $0 <image_file.img>"
    exit 1
fi

SECTOR_SIZE=512
MOUNT_BASE="/mnt"
LOOP_TRACK_FILE="/tmp/mounted_loops.txt"

echo "[*] 分析镜像: $IMG"
echo

# 清空旧的记录
> "$LOOP_TRACK_FILE"

# 使用 fdisk 获取分区信息
part_info=$(fdisk -l "$IMG" | grep "^$IMG")

i=1
echo "$part_info" | while read -r line; do
    start_sector=$(echo "$line" | awk '{print $2}')
    size_sector=$(echo "$line" | awk '{print $4}')
    fstype=$(echo "$line" | awk '{$1=$2=$3=$4=""; print $0}' | sed 's/^ *//')

    offset=$((start_sector * SECTOR_SIZE))
    mount_point="$MOUNT_BASE/img$i"

    echo "[+] 分区$i:"
    echo "    起始扇区 : $start_sector"
    echo "    偏移字节 : $offset"
    echo "    大小     : $((size_sector * SECTOR_SIZE / 1024 / 1024)) MB"
    echo "    类型     : $fstype"
    echo "    挂载点   : $mount_point"

    sudo mkdir -p "$mount_point"

    LOOPDEV=$(sudo losetup --find --show --offset "$offset" "$IMG")
    if sudo mount "$LOOPDEV" "$mount_point"; then
        echo "    ✅ 挂载成功 (loop 设备: $LOOPDEV)"
        echo "$LOOPDEV $mount_point" >> "$LOOP_TRACK_FILE"
    else
        echo "    ❌ 挂载失败"
        sudo losetup -d "$LOOPDEV"
    fi

    echo
    ((i++))
done





# ```

# ---

# ## ✅ 使用方法：

# ```bash
# chmod +x mount_img.sh
# ./mount_img.sh Orangepi5plus_1.2.0*.img
# ```

# ---

# ## ✅ 示例输出：

# ```
# [*] 分析镜像: Orangepi5plus_1.2.0_debian_bullseye.img

# [+] 分区1:
#     起始扇区 : 61440
#     偏移字节 : 31457280
#     大小     : 1024 MB
#     类型     : Linux 扩展启动
#     挂载点   : /mnt/img1
#     ✅ 挂载成功

# [+] 分区2:
#     起始扇区 : 2158592
#     偏移字节 : 1105719296
#     大小     : 2442 MB
#     类型     : Linux 文件系统
#     挂载点   : /mnt/img2
#     ✅ 挂载成功
# ```

# ---

# ## ✅ 卸载所有挂载点（可选）：

# ```bash
# sudo umount /mnt/img1
# sudo umount /mnt/img2
# ```

# ---

# 是否需要我添加自动卸载功能或支持提取文件？
