cmake_minimum_required (VERSION 3.12.1)

aux_source_directory(. DIR__NET_SRCS)
add_library(rabbit_net ${DIR__NET_SRCS})
#install(TARGETS rabbit_net DESTINATION lib)
target_link_libraries(rabbit_net rabbit_base pthread)
file(GLOB HEADERS "*.h")
install(FILES ${HEADERS} DESTINATION /usr/local/include)
install(TARGETS rabbit_net DESTINATION /usr/local/lib)

