cmake_minimum_required (VERSION 3.12.1)

project(echo)

include_directories(../../net/)
include_directories(../../base/)
include_directories(../../http/)

add_executable(http_server http_server.cpp HttpServer.cpp)
target_link_libraries(http_server rabbit_base rabbit_net rabbit_http) 

#add_executable(echo_client echo_client.cpp)
#target_link_libraries(echo_client rabbit_base rabbit_net)
