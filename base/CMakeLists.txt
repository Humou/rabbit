cmake_minimum_required (VERSION 3.12.1)

aux_source_directory(. DIR__BASE_SRCS)
add_library(rabbit_base ${DIR__BASE_SRCS})

file(GLOB HEADERS "*.h")
install(FILES ${HEADERS} DESTINATION /usr/local/include)
install(TARGETS rabbit_base DESTINATION /usr/local/lib)

