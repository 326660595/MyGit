cmake_minimum_required(VERSION 3.10)  # 指定CMake的最低版本要求

project(BoostLogExample)  # 项目名称

# 找到Boost库，确保Boost库的版本符合要求
find_package(Boost 1.74.0 COMPONENTS log log_setup thread system REQUIRED)

# 包含Boost头文件的路径
include_directories(${Boost_INCLUDE_DIRS})

# 定义一个可执行文件，其源文件为log.cpp
add_executable(my_log_program log.cpp)

# 链接Boost库
target_link_libraries(my_log_program ${Boost_LIBRARIES})


add_executable(log_to_file log_to_file.cpp)
# 链接Boost库
target_link_libraries(log_to_file ${Boost_LIBRARIES})


