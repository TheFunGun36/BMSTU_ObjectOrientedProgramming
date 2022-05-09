#pragma once
#include "jexception.h"

namespace Jora {

class ModelBadAlloc : public Exception {
public:
    inline ModelBadAlloc(const char* file, const char* function, int line)
        : Exception("Failed appending new element to model", file, function, line) {
    };
};

class ModelOutOfRange : public Exception {
public:
    inline ModelOutOfRange(const char* file, const char* function, int line)
        : Exception("Index out of range", file, function, line) {
    };
};

}
