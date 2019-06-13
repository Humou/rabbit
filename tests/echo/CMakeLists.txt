cmake_minimum_required (VERSION 3.12.1)

project(echo)

aux_source_directory(. DIR_ECHO_SRCs)
#link_directories("/home/hu/rabbit/base/build")
add_executable(echo ${DIR_ECHO_SRCs})
target_link_libraries(echo rabbit_base rabbit_net)
