#pragma once
#include <exception>

namespace jora {
    class Exception : public std::exception {
    public:
        inline Exception(const char* message, const char* file, const char* function, int line);

        virtual inline const char* what() const noexcept override;
        virtual inline const char* file() const noexcept final;
        virtual inline const char* function() const noexcept final;
        virtual inline int line() const noexcept final;

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
    };


    /********** IMPLEMENTATION **********/
    inline Exception::Exception(const char* message, const char* file, const char* function, int line)
        : std::exception()
        , _message(message)
        , _file(file)
        , _function(function)
        , _line(line) {}
    inline const char* Exception::what() const noexcept {
        return message();
    }
    inline const char* Exception::file() const noexcept {
        return _file;
    }
    inline const char* Exception::function() const noexcept {
        return _function;
    }
    inline int Exception::line() const noexcept {
        return _line;
    }
    inline const char* Exception::message() const noexcept {
        return _message;
    }
    inline void Exception::setFile(const char* val) noexcept {
        _file = val;
    }
    inline void Exception::setFunction(const char* val) noexcept {
        _function = val;
    }
    inline void Exception::setLine(int val) noexcept {
        _line = val;
    }
}
