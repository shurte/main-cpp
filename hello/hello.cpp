#include <hello.hpp>

#include <iostream>

Hello::Hello() {
    std::cout << "Hello" << '\n';
}

Hello::~Hello() {
    std::cout << "Bye" << '\n';
}