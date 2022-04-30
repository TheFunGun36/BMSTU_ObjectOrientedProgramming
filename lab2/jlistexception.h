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

    class ListDifferentListIteratorException : public ListException {
    public:
        ListDifferentListIteratorException(const char* file, const char* function, int line)
            : ListException("list does not contain iterator", file, function, line) {}
    };

    class ListBadIteratorRangeException : public ListException {
    public:
        ListBadIteratorRangeException(const char* file, const char* function, int line)
            : ListException("iterator pair does not form valid list range", file, function, line) {}
    };
}