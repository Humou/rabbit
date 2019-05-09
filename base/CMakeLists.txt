cmake_minimum_required (VERSION 3.12.1)

project(rabbit_base)

aux_source_directory(. DIR_SRCS)
add_library(rabbit_base ${DIR_SRCS})
install(TARGETS rabbit_base DESTINATION lib)
