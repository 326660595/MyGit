#########################
#test
#########################
project(can_server)

set(SOURCE_FILES
                can_service.cpp
                can_service.h
)

add_executable(${PROJECT_NAME} can_service.cpp)

# add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
                        r_canj1939
)