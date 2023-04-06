project(charge-core)

add_executable(ChargerCore main.c)

#生成静态库
add_library(a-hello_library STATIC
                main.c
        )

#生成动态库
add_library(so-hello_library SHARED 
                main.c
    )

INSTALL(TARGETS ChargerCore so-hello_library a-hello_library 
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# install({FILES | PROGRAMS} <file>... [...])
# install(DIRECTORY <dir>... [...])
# install(SCRIPT <file> [...])
# install(CODE <code> [...])
# install(EXPORT <export-name> [...])