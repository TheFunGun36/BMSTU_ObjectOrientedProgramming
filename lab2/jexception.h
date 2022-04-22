#include <exception>

namespace jora {
    class Exception : public std::exception {
    public:
        Exception(const char *message, const char *file, const char *function, int line)
            : std::exception(message)
            , _file(file)
            , _function(function)
            , _line(line) {}

        virtual inline const char *file() const final { return _file; }
        virtual inline const char *function() const final { return _function; }
        virtual inline int line() const final { return _line; }

    protected:
        virtual inline void setFile(const char *val) final { _file = val; }
        virtual inline void setFunction(const char *val) final { _function = val; }
        virtual inline void setLine(const char *val) final { _line = val; }

    private:
        const char *_file;
        const char *_function;
        int _line;
    };
}
