#pragma once
#include "Types.h"
#include <cmath>
#include <algorithm>

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

inline Vector3D vector3DAdd(Vector3D a, Vector3D b) {
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    return a;
}

inline Vector3D vector3DSub(Vector3D a, Vector3D b) {
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    return a;

}

inline Point2D point2DFrom3D(Point3D point) {
    Point2D result;
    result.x = point.x;
    result.y = point.y;
    return result;
}

inline void pointToScreenCoords(Point2D &point) {
    point.y = -point.y;
}
