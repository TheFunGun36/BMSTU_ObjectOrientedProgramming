#pragma once
#include <cmath>
#include <algorithm>

typedef double Real;

struct Point3D {
    Real x;
    Real y;
    Real z;
};

struct Point2D {
    Real x;
    Real y;
};

typedef Point3D Vector3D;
typedef Point2D Vector2D;

inline bool isZero(Real v) {
    return abs(v) <= 0;
}
