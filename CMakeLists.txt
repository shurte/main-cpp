cmake_minimum_required(VERSION 3.31)
project(Hello)

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    message("Compiler on Windows: ${CMAKE_CXX_COMPILER_ID}")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    message("Compiler on MacOS: ${CMAKE_CXX_COMPILER_ID}")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    message("Compiler on Unix: ${CMAKE_CXX_COMPILER_ID}")
endif()

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(CPM)

cpmaddpackage("gh:catchorg/Catch2#v3.10.0")

add_subdirectory(hello)
add_subdirectory(ui)

add_executable(main Main.cpp)
target_include_directories(main PUBLIC ${CMAKE_SOURCE_DIR}/)
target_link_libraries(main hello)
target_include_directories(main PUBLIC ${CMAKE_SOURCE_DIR}/hello/)
target_link_libraries(main ui)
target_include_directories(main PUBLIC ${CMAKE_SOURCE_DIR}/ui/)

add_executable(test Test.cpp)
target_link_libraries(test hello)
target_include_directories(test PUBLIC ${CMAKE_SOURCE_DIR}/hello/)

target_link_libraries(test Catch2WithMain)

message("Build type: ${CMAKE_BUILD_TYPE}")

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    message("Debug build type: ${CMAKE_BUILD_TYPE}.")
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    message("Release build type: ${CMAKE_BUILD_TYPE}.")
else ()
    message("Build type is not defined.")
endif()

add_custom_target(
    FinalMessage ALL
    ${CMAKE_COMMAND} -E cmake_echo_color --cyan
    COMMENT "Final Message ${CMAKE_BUILD_TYPE}"
)

if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_custom_command(
        TARGET main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy "${SDL2_BINARY_DIR}\\Debug\\SDL2d.dll" "${CMAKE_BINARY_DIR}\\Debug\\SDL2d.dll"
        COMMENT "SDL2d.dll copied"
    )
    add_custom_command(
        TARGET main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy "${glew_BINARY_DIR}\\bin\\Debug\\glew-sharedd.dll" "${CMAKE_BINARY_DIR}\\Debug\\glew-sharedd.dll"
        COMMENT "SDL2d.dll copied"
    )
endif()

if (CMAKE_GENERATOR MATCHES "MinGW Makefiles")
    add_custom_command(
        TARGET main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy "${SDL2_BINARY_DIR}/SDL2d.dll" "${CMAKE_BINARY_DIR}/SDL2d.dll"
        COMMENT "SDL2.dll copied"
    )
    add_custom_command(
        TARGET main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy "${glew_BINARY_DIR}/bin/libglew-sharedd.dll" "${CMAKE_BINARY_DIR}/libglew-sharedd.dll"
        COMMENT "SDL2.dll copied"
    ) 
endif()