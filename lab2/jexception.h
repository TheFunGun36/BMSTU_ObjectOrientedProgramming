#include <exception>

namespace jora {
    class Exception : public std::exception {
    public:
        Exception(const char *message, const char *file, const char *function, int line)
            : std::exception()
            , _message(message)
            , _file(file)
            , _function(function)
            , _line(line) {}

        virtual const char *what() const noexcept override { return message(); }
        virtual inline const char *file() const noexcept final { return _file; }
        virtual inline const char *function() const noexcept final { return _function; }
        virtual inline int line() const noexcept final { return _line; }

    protected:
        virtual inline const char *message() const noexcept final { return _message; }
        virtual inline void setFile(const char *val) noexcept final { _file = val; }
        virtual inline void setFunction(const char *val) noexcept final { _function = val; }
        virtual inline void setLine(int val) noexcept final { _line = val; }

    private:
        const char *_message;
        const char *_file;
        const char *_function;
        int _line;
    };
}
