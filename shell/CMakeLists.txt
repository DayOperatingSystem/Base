#file(GLOB_RECURSE HEADERS *.h)
#file(GLOB_RECURSE SOURCES *.c*)

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

BISON_TARGET(parser parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.cc)
FLEX_TARGET(lexer lexer.l  ${CMAKE_CURRENT_BINARY_DIR}/lexer.cc)
ADD_FLEX_BISON_DEPENDENCY(lexer parser)

set(SOURCES
    main.cpp
)

add_executable(shell.elf ${SOURCES} ${HEADERS})# ${BISON_parser_OUTPUTS} ${FLEX_lexer_OUTPUTS})

include_directories(${APPLICATION_INCLUDES} ${CMAKE_CURRENT_SOURCE_DIR}/tlli-master ${CMAKE_CURRENT_SOURCE_DIR}/tlli-master/include ${CMAKE_CURRENT_SOURCE_DIR}/tlli-master/src/util
${CMAKE_CURRENT_SOURCE_DIR}/tlli-master/src/include)

install(TARGETS shell.elf DESTINATION ${CMAKE_INSTALL_PREFIX}/image)

target_link_libraries(shell.elf dayos m)
include_directories(${LIBDAYOS_INCLUDE})
