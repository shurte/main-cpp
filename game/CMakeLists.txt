file(GLOB SOURCES *.cpp)

add_library(game ${SOURCES})
target_include_directories(game PUBLIC ${CMAKE_SOURCE_DIR}/game/)