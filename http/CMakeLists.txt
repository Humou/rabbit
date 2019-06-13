cmake_minimum_required (VERSION 3.12.1)

aux_source_directory(. DIR_LIB_SRCS)
add_library(rabbit_http ${DIR_LIB_SRCS})

file(GLOB HEADERS "*.h")
install(FILES ${HEADERS} DESTINATION /usr/local/include)
install(TARGETS rabbit_http DESTINATION /usr/local/lib)

