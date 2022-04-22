#pragma once
#include "jexception.h"

namespace jora {
    class IteratorExpiredException : public Exception {
        IteratorExpiredException(const char *file, const char *function, int line)
            : Exception("tried to access expired (or uninitialized) iterator", file, function, line) {}
    };
}
