add_executable(test Test.cpp)
target_link_libraries(test hello)
target_include_directories(test PUBLIC ${CMAKE_SOURCE_DIR}/hello/)
target_link_libraries(test Catch2WithMain)
