#pragma once
#include "jexception.h"

namespace jora {
    class IteratorException : public Exception {
    public:
        IteratorException(const char *message, const char *file, const char *function, int line)
            : Exception(message, file, function, line) {}
    };

    class IteratorExpiredException : public IteratorException {
    public:
        IteratorExpiredException(const char *file, const char *function, int line)
            : IteratorException("tried to access expired, uninitialized iterator (maybe excessed end?)", file, function, line) {}
    };
}
