add_library(hello Hello.cpp)
target_include_directories(hello PUBLIC ${CMAKE_SOURCE_DIR}/hello/)