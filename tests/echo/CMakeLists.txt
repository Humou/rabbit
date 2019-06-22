cmake_minimum_required (VERSION 3.12.1)

project(echo)

include_directories(../../net/)
include_directories(../../base/)
include_directories(../../http/)

add_executable(echo_server Acceptor.cpp EchoHandler.cpp EchoServer.cpp echo_server.cpp)
target_link_libraries(echo_server rabbit_base rabbit_net)

#add_executable(echo_client echo_client.cpp)
#target_link_libraries(echo_client rabbit_base rabbit_net)
