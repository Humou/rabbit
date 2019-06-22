cmake_minimum_required (VERSION 3.12.1)

project(test)

aux_source_directory(. DIR_TEST_SRCs)
add_subdirectory(echo)
add_subdirectory(http_test)
add_executable(test ${DIR_TEST_SRCs})
target_link_libraries(test rabbit_base)
