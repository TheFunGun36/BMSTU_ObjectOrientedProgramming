#pragma once
#include <cmath>
#include <algorithm>
#include <cstring>

struct Point3D {
    double x;
    double y;
    double z;
};

struct Point2D {
    double x;
    double y;
};

typedef Point3D Vector3D;
typedef Point2D Vector2D;

inline bool isZero(double v) {
    return abs(v) <= 1e-10;
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

inline Point2D point2DMultiply(Point2D point, double k) {
    point.x *= k;
    point.y *= k;
    return point;
}

inline Point3D point3DEmpty() {
    Point3D point;
    memset(&point, 0, sizeof(Point3D));
    return point;
}
