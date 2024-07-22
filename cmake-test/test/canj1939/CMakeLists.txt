#########################
#test
#########################
project(canj1939)

set(SOURCE_FILES
        socketcan_asio.cpp
        socketcan_asio.h
)

add_executable(test_socketcan socketcan_asio.cpp)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        
)