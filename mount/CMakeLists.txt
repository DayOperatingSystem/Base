file(GLOB_RECURSE HEADERS *.h)
file(GLOB_RECURSE SOURCES *.c*)

add_executable(mount ${SOURCES} ${HEADERS})
target_link_libraries(mount dayos m)

install(TARGETS mount DESTINATION ${CMAKE_INSTALL_PREFIX}/image)
include_directories(${LIBDAYOS_INCLUDE})
