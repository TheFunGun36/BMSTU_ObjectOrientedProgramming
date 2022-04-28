#pragma once
#include "jexception.h"

namespace jora {
    class NodeException : public Exception {
    public:
        NodeException(const char* message, const char* file, const char* function, int line)
            : Exception(message, file, function, line) {}
    };

    class NodeBadAllocException : public NodeException {
    public:
        NodeBadAllocException(const char* file, const char* function, int line)
            : NodeException("failed to allocate memory for new Node", file, function, line) {}
    };
}