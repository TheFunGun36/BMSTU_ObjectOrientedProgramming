#pragma once
#include "jexception.h"
namespace Jora {

class PointsArrayExpired : public Exception {
public:
    inline PointsArrayExpired(const char* file, const char* function, int line)
        : Exception("Points array is expired (uninitialized or deleted)", file, function, line) {
    };
};

}
