########################################################################
#charge-core cmake
#run cmake: #cd build; #cmake ..; #make ;
#clean : #rm -rf ./build ./out
############################################################################
project(ABB-CHARGERCORE)
cmake_minimum_required(VERSION 3.18)

# set(CMAKE_SYSTEM_NAME Linux)
# set(CMAKE_SYSTEM_PROCESSOR arm64)
#set your gcc or set environment.
# set(CMAKE_C_COMPILER /usr/bin/aarch64-linux-gnu-gcc)

# set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/out)#设置输出目标文件路径

set(CMAKE_INSTALL_PREFIX  ${PROJECT_SOURCE_DIR}/build/install)#设置安装路径

add_subdirectory(src)
add_subdirectory(test)
