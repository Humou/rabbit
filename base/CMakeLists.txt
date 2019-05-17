cmake_minimum_required (VERSION 3.12.1)

#project(rabbit_base)

aux_source_directory(. DIR__LIB_SRCS)
add_library(rabbit_base ${DIR__LIB_SRCS})
#install(TARGETS rabbit_base DESTINATION lib)
