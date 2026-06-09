# Hello

## Setup
- g++ compiler. For example, mingw64 in "c:/_programs/mingw64/bin"
    ```cmd
    set PATH=%PATH%;c:/_programs/mingw64/bin
    ```
- CMake. For example, in "c:/_programs/cmake/bin"
    ```cmd
    set PATH=%PATH%;c:/_programs/cmake/bin
    ```
- Make ???

## Build
- the CMake build command
    ```cmd
    cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug
    ```
- build the C++ code
    ```cmd
    cmake --build build
    ```

## Run
- run the program
    ```cmd
    build\main.exe 
    ```