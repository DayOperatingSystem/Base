file(GLOB_RECURSE HEADERS *.h)
file(GLOB_RECURSE SOURCES *.c*)

add_executable(init.elf ${SOURCES} ${HEADERS})
install(TARGETS init.elf DESTINATION ${CMAKE_INSTALL_PREFIX}/image)

# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -nostartfiles")
target_link_libraries(init.elf dayos m)
include_directories(${LIBDAYOS_INCLUDE})