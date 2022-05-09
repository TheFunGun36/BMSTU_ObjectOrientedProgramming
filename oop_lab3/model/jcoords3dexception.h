#pragma once
#include "jexception.h"
namespace Jora {

class CoordsOutOfRange : public Exception {
public:
    inline CoordsOutOfRange(const char* file, const char* function, int line)
    : Exception("Coords index out of range. Only 0, 1 or 2 are available for use", file, function, line) {};
};

}
