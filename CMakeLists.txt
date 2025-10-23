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

message("Build type: ${CMAKE_BUILD_TYPE}")

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    message("Debug build type: ${CMAKE_BUILD_TYPE}.")
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    message("Release build type: ${CMAKE_BUILD_TYPE}.")
else ()
    message("Build type is not defined.")
endif()

add_custom_target( FinalMessage ALL
    ${CMAKE_COMMAND} -E cmake_echo_color --cyan
    COMMENT "Final Message ${CMAKE_BUILD_TYPE}" )