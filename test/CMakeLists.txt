cmake_minimum_required (VERSION 3.12.1)

project(test)

aux_source_directory(. DIR_SRCS)

#add_subdirectory(../base)

#INCLUDE_DIRECTORIES("/home/hu/rabbit/base/include")
#find_library(base.a /home/hu/rabbit/base/build/)

include_directories(
    /home/hu/rabbit/base/
)

add_executable(test ${DIR_SRCS})

target_link_libraries(test rabbit_base)
