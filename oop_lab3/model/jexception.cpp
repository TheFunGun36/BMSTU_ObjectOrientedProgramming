#include "pch.h"
#include "jexception.h"

namespace Jora {

Exception::Exception(const char* message, const char* file, const char* function, int line)
    : std::exception()
    , _message(message)
    , _file(file)
    , _function(function)
    , _line(line)
    , _time(std::chrono::high_resolution_clock::now()) {}
const char* Exception::what() const noexcept {
    return message();
}
const char* Exception::file() const noexcept {
    return _file;
}
const char* Exception::function() const noexcept {
    return _function;
}
int Exception::line() const noexcept {
    return _line;
}
Exception::TimePoint Exception::time() const noexcept {
    return _time;
}
const char* Exception::message() const noexcept {
    return _message;
}
void Exception::setFile(const char* val) noexcept {
    _file = val;
}
void Exception::setFunction(const char* val) noexcept {
    _function = val;
}
void Exception::setLine(int val) noexcept {
    _line = val;
}
}
