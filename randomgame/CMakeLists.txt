file(GLOB_RECURSE HEADERS *.h)
file(GLOB_RECURSE SOURCES *.c*)

add_executable(randomgame.elf ${SOURCES} ${HEADERS})
target_link_libraries(randomgame.elf dayos m)

install(TARGETS randomgame.elf DESTINATION ${CMAKE_INSTALL_PREFIX}/image)
include_directories(${LIBDAYOS_INCLUDE})