file(GLOB_RECURSE HEADERS *.h)
file(GLOB_RECURSE SOURCES *.c*)

add_executable(graphicstest.elf ${SOURCES} ${HEADERS})
target_link_libraries(graphicstest.elf dayos m)

install(TARGETS graphicstest.elf DESTINATION ${CMAKE_INSTALL_PREFIX}/image)
include_directories(${LIBDAYOS_INCLUDE})