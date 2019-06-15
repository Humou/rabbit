cmake_minimum_required (VERSION 3.12.1)

project(echo)

#aux_source_directory(. DIR_ECHO_SRCs)
#link_directories("/home/hu/rabbit/base/build")
add_executable(echo_server echo_server.cpp)
target_link_libraries(echo_server rabbit_base rabbit_net)

add_executable(echo_client echo_client.cpp)
target_link_libraries(echo_client rabbit_base rabbit_net)
