file(GLOB_RECURSE HEADERS *.h)
file(GLOB_RECURSE SOURCES *.c*)

add_executable(mkdir ${SOURCES} ${HEADERS})
target_link_libraries(mkdir dayos m)

install(TARGETS mkdir DESTINATION ${CMAKE_INSTALL_PREFIX}/image)
include_directories(${LIBDAYOS_INCLUDE})
