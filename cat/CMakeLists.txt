file(GLOB_RECURSE HEADERS *.h)
file(GLOB_RECURSE SOURCES *.c*)

add_executable(cat.elf ${SOURCES} ${HEADERS})
target_link_libraries(cat.elf dayos m)

install(TARGETS cat.elf DESTINATION ${CMAKE_INSTALL_PREFIX}/image)
include_directories(${LIBDAYOS_INCLUDE})
