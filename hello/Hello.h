#pragma once

#include <iostream>
#include <stdint.h>
#include <string>

#ifdef _WIN32
#include <wtypes.h>
#else
#include <limits.h>
#include <unistd.h>     //readlink
#endif

namespace hello {

std::string getAppDirectory();
void write(const std::string& info);
void clock();
void sleep(const uint64_t milliseconds);

};

class Hello {
    public:
        Hello();
        ~Hello();  
};
