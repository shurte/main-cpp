cmake_minimum_required(VERSION 3.31)
project(Hello)
add_executable(main main.cpp)
target_include_directories(main PUBLIC ${CMAKE_SOURCE_DIR}/.)