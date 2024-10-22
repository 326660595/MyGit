# ########################

# test

# ########################

cmake_minimum_required(VERSION 3.10)

project(t_nomho_json)

# 添加子目录
add_subdirectory(nlohmann)

# 定义可执行文件
add_executable(${PROJECT_NAME} test1.cpp)

# 链接库
target_link_libraries(${PROJECT_NAME}

    json-nlohmann
)

# 指定包含目录
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/nlohmann)

add_executable(pjson parsJsonTest.cpp
)

target_include_directories(pjson PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(pjson
    json-nlohmann
)