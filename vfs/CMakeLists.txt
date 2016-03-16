file(GLOB_RECURSE HEADERS *.h)
file(GLOB_RECURSE SOURCES main.cpp FileSystem.cpp)

add_executable(vfs.elf ${SOURCES})
install(TARGETS vfs.elf DESTINATION ${CMAKE_INSTALL_PREFIX}/image)
target_link_libraries(vfs.elf stdc++ gcc dayos m)

include_directories(${LIBDAYOS_INCLUDE})
