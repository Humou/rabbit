cmake_minimum_required (VERSION 3.12.1)

project(server)

aux_source_directory(. DIR_SRCS)

add_subdirectory(base)
add_subdirectory(http)

add_executable(server ${DIR_SRCS})

target_link_libraries(server rabbit_base rabbit_http pthread)
