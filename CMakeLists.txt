cmake_minimum_required(VERSION 3.17)
project(exam4_prep)

set(CMAKE_CXX_STANDARD 11)

add_library(ip ip.h ip.cpp)
add_executable(exam4_prep main.cpp)
target_link_libraries(exam4_prep ip)