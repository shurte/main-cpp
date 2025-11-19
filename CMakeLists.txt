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

set(BETWEEN_BUILD_FOLDER "")

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    message("Debug build type: ${CMAKE_BUILD_TYPE}.")
    set(DEBUG_INDEX "d")
    if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
        set(BETWEEN_BUILD_FOLDER "Debug/")
    endif()
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    message("Release build type: ${CMAKE_BUILD_TYPE}.")
    set(DEBUG_INDEX "")
    if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
        set(BETWEEN_BUILD_FOLDER "Release/")
    endif()
else ()
    message("Build type is not defined.")
    set(DEBUG_INDEX "")
    if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
        set(BETWEEN_BUILD_FOLDER "Debug/")
    endif()
endif()

add_custom_target(
    FinalMessage ALL
    ${CMAKE_COMMAND} -E cmake_echo_color --cyan
    COMMENT "Final Message ${CMAKE_BUILD_TYPE}"
)

set(DLL_PREFIX "lib")
if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set(DLL_PREFIX "")
endif()

if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC" OR CMAKE_GENERATOR MATCHES "MinGW Makefiles")
    add_custom_command(
        TARGET main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy "${SDL2_BINARY_DIR}/${BETWEEN_BUILD_FOLDER}SDL2${DEBUG_INDEX}.dll" "${CMAKE_BINARY_DIR}/${BETWEEN_BUILD_FOLDER}SDL2${DEBUG_INDEX}.dll"
        COMMENT "SDL2${DEBUG_INDEX}.dll copied"
    )
    add_custom_command(
        TARGET main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy "${glew_BINARY_DIR}/bin/${BETWEEN_BUILD_FOLDER}${DLL_PREFIX}glew-shared${DEBUG_INDEX}.dll" 
            "${CMAKE_BINARY_DIR}/${BETWEEN_BUILD_FOLDER}${DLL_PREFIX}glew-shared${DEBUG_INDEX}.dll"
        COMMENT "SDL2${DEBUG_INDEX}.dll copied"
    )
endif()