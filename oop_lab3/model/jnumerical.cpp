#include "pch.h"
#include "jnumerical.h"

namespace Jora {

bool realEq(real a, real b) {
    return abs(a - b) < 1e-10;
}

}
