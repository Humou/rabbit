cmake_minimum_required (VERSION 3.12.1)

#project(rabbit_http)

aux_source_directory(. DIR_LIB_SRCS)
add_library(rabbit_http ${DIR_LIB_SRCS})
#install(TARGETS rabbit_http DESTINATION lib)
