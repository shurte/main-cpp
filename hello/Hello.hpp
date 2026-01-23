#pragma once

#include <iostream>
#include <string>

#ifdef _WIN32
#include <wtypes.h>
#else
#include <limits.h>
#include <unistd.h>     //readlink
#endif

namespace hello {

std::string getAppDirectory();

};

class Hello {
    public:
        Hello();
        ~Hello();
        void write(const std::string& info) const;
        void clock() const;
};
