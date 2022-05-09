#pragma once
#include "jexception.h"
namespace Jora {

class FileException : public Exception {
public:
    inline virtual const char* fileName() const noexcept { return _fileName.c_str(); }
    inline virtual int fileLine() const noexcept { return _fileLine; }

    inline virtual void setFileName(std::string &&str) noexcept { _fileName = std::move(str); }
    inline virtual void setFileLine(int value) noexcept { _fileLine = value; }
protected:
    inline FileException(const char* msg, const char* file, const char* function, int line)
        : Exception(msg, file, function, line)
        , _fileName()
        , _fileLine(-1) {
    }

    std::string _fileName;
    int _fileLine;
};

class FileNotOpen : public Exception {
public:
    inline FileNotOpen(const char* file, const char* function, int line)
        : Exception("Failed to open file", file, function, line) {
    };
};

class FileInvalidVertex : public Exception {
public:
    inline FileInvalidVertex(const char* file, const char* function, int line)
        : Exception("Invalid vertex data in file", file, function, line) {
    };
};

class FileInvalidFace : public Exception {
public:
    inline FileInvalidFace(const char* file, const char* function, int line)
        : Exception("Invalid face data in file", file, function, line) {
    };
};

}
