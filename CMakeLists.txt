cmake_minimum_required(VERSION 3.31)
project(Hello)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(CPM)

cpmaddpackage("gh:catchorg/Catch2#v3.10.0")

add_subdirectory(hello)

add_executable(main main.cpp)
target_link_libraries(main hello)
target_include_directories(main PUBLIC ${CMAKE_SOURCE_DIR}/hello/)

add_executable(test test.cpp)
target_link_libraries(test hello)
target_link_libraries(test Catch2WithMain)
target_include_directories(test PUBLIC ${CMAKE_SOURCE_DIR}/hello/)