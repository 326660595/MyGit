#########################
#test
#########################
project(t111)

set(SOURCE_FILES
                t.cpp
)

add_executable(${PROJECT_NAME} t.cpp)

# add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

# target_include_directories(${PROJECT_NAME} PUBLIC
#         ${CMAKE_CURRENT_SOURCE_DIR}
# )

# target_link_libraries(${PROJECT_NAME}
#                         r_canj1939
# )