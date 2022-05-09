#pragma once
#include <cmath>

namespace Jora {
using real = double;

namespace {
    constexpr real tolerance = 1e-10;
}

inline bool realEq(real a, real b) { return abs(a - b) <= tolerance; }
}
