cmake_minimum_required(VERSION 2.8)

ADD_DEFINITIONS(
  -Wall
  -g
  -O2
  -std=c++11
)

project(test)

include_directories(
/usr/local/include/iz-c
)

add_executable (sample3 sample3.cpp)
target_link_libraries (sample3 iz)