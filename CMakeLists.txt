cmake_minimum_required(VERSION 3.31)
project(Hello)

add_subdirectory(hello)

add_executable(main main.cpp)
target_link_libraries(main hello)
target_include_directories(main PUBLIC ${CMAKE_SOURCE_DIR}/hello/)