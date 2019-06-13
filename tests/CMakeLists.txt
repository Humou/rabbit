cmake_minimum_required (VERSION 3.12.1)

project(test)

aux_source_directory(. DIR_TEST_SRCs)
#link_directories("/home/hu/rabbit/base/build")
add_executable(test ${DIR_TEST_SRCs})
target_link_libraries(test rabbit_base)
