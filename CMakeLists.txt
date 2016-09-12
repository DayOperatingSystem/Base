cmake_minimum_required(VERSION 2.8.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED on)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED on)

project(DayOSBase)

set(CMAKE_MODULE_PATH
  ${CMAKE_SOURCE_DIR}/CMake
  ${CMAKE_MODULE_PATH}
)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/image/)
message("Base system output to " ${EXECUTABLE_OUTPUT_PATH})
set(RUNTIME_OUTPUT_DIRECTORY ${EXECUTABLE_OUTPUT_PATH})

set(ASM_EXTENSION *.S)
set(CMAKE_C_FLAGS "-Wall -g") # -pedantic-errors")
set(CMAKE_CXX_FLAGS "-g -fno-use-cxa-atexit -Wall -Wextra -pedantic-errors")

add_subdirectory(init)
add_subdirectory(shell)
add_subdirectory(vfs)
add_subdirectory(uname)
add_subdirectory(cat)
add_subdirectory(mount)
add_subdirectory(ls)
