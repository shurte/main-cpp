cpmaddpackage("gh:libsdl-org/SDL#release-2.32.8")
cpmaddpackage("gh:Perlmint/glew-cmake#origin/master")

add_library(ui Window.cpp)
target_include_directories(ui PUBLIC ${CMAKE_SOURCE_DIR}/ui/)

target_link_libraries(ui SDL2)
target_link_libraries(ui libglew_shared)
