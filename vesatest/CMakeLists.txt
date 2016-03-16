file(GLOB_RECURSE HEADERS *.h)
file(GLOB_RECURSE SOURCES *.c*)

add_executable(vesatest.elf ${SOURCES} ${HEADERS})
target_link_libraries(vesatest.elf dayos m stdc++)

install(TARGETS vesatest.elf DESTINATION ${CMAKE_INSTALL_PREFIX}/image)
include_directories(${LIBDAYOS_INCLUDE})
