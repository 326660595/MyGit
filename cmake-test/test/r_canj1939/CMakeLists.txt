#########################
#test
#########################
project(r_canj1939)

set(SOURCE_FILES
        SocketCanJ1939.cpp
)

# add_executable(SocketJ1939test SocketCanJ1939.cpp)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)