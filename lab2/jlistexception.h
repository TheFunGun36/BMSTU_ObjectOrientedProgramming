#pragma once
#include "jexception.h"

namespace jora {
    class ListException : public Exception {
    public:
        ListException(const char* message, const char* file, const char* function, int line)
            : Exception(message, file, function, line) {}
    };

    class ListBadAllocException : public ListException {
    public:
        ListBadAllocException(const char* file, const char* function, int line)
            : ListException("failed to allocate memory for new list element", file, function, line) {}
    };

    class ListCArrayNullptrException : public ListException {
    public:
        ListCArrayNullptrException(const char* file, const char* function, int line)
            : ListException("input CArray is nullptr", file, function, line) {}
    };

    class ListEmptyException : public ListException {
    public:
        ListEmptyException(const char* file, const char* function, int line)
            : ListException("tried to access element of an empty list", file, function, line) {}
    };

    class ListNotImplementedException : public ListException {
    public:
        ListNotImplementedException(const char* file, const char* function, int line)
            : ListException("not implemented", file, function, line) {}
    };
}