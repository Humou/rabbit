cmake_minimum_required (VERSION 3.12.1)

project(server)

#aux_source_directory(. DIR_SRCS)

add_subdirectory(base)
add_subdirectory(net)
add_subdirectory(http)
add_subdirectory(tests)

