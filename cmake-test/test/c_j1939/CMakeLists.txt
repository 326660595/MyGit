#########################
#test
#########################
project(c_j1939)

set(SOURCE_FILES
        test_can.c
)

add_executable(test_can test_can.c)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)