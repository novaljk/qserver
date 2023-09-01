add_subdirectory(base)

file (GLOB SRC_SOURCES "*.cpp")
add_executable(qserver ${SRC_SOURCES})
target_link_libraries(
    qserver
    qserver_base
    ${ARGN}
)