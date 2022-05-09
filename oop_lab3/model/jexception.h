#pragma once
#include <exception>
#include <chrono>

namespace Jora {
class Exception : public std::exception {
public:
    using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;
    Exception(const char* message, const char* file, const char* function, int line);

    virtual inline const char* what() const noexcept override;
    virtual inline const char* file() const noexcept final;
    virtual inline const char* function() const noexcept final;
    virtual inline int line() const noexcept final;
    virtual inline TimePoint time() const noexcept final;

protected:
    virtual inline const char* message() const noexcept final;
    virtual inline void setFile(const char* val) noexcept final;
    virtual inline void setFunction(const char* val) noexcept final;
    virtual inline void setLine(int val) noexcept final;

private:
    const char* _message;
    const char* _file;
    const char* _function;
    int _line;
    TimePoint _time;
};
}
