#include <hello.hpp>

Hello::Hello() {
    std::cout << "Hello" << '\n';
}

Hello::~Hello() {
    std::cout << "Bye" << '\n';
}

void Hello::write(const std::string& info) {
    std::cout << info.c_str() << '\n';
}

std::string hello::getAppDirectory() {
    size_t BUF_SIZE = 1024;
    char* fileName = new char[BUF_SIZE];
#ifdef _WIN32
    GetModuleFileName(nullptr, fileName, BUF_SIZE);
    std::string directory(fileName);
    int lastSlash = directory.find_last_of('\\');
    directory = directory.substr(0, lastSlash);
#else
    ssize_t count = readlink("/proc/self/exe", fileName, BUF_SIZE);
    std::string directory(fileName, (count > 0) ? count : 0);
#endif
    return directory;
}
