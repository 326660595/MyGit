project(charge-core)

add_executable(ChargerCore main.c)

INSTALL(TARGETS ChargerCore
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# install({FILES | PROGRAMS} <file>... [...])
# install(DIRECTORY <dir>... [...])
# install(SCRIPT <file> [...])
# install(CODE <code> [...])
# install(EXPORT <export-name> [...])