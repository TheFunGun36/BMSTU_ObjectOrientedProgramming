#include "pch.h"
#include "jpoint3d.h"

namespace Jora {

Point3D::Point3D(const Vector3D& value)
    : _value(value) {}

const Vector3D& Point3D::value() const {
    return _value;
}

Vector3D& Point3D::value() {
    return _value;
}

void Point3D::setValue(const Vector3D& point) {
    _value = point;
}

void Point3D::scale(const Vector3D& factors) {
    for (int i = 0; i < 3; i++)
        _value[i] *= factors[i];
}

void Point3D::rotate(const Angle& x, const Angle& y, const Angle& z) noexcept {
    Angle angles[] = { x, y, z };
    size_t ix = 1;
    size_t iy = 2;
    size_t iz = 0;

    for (int i = 0; i < 3; i++) {
        Vector3D newPoint(_value);
        newPoint[ix] = _value[ix] * angles[iz].cos() - _value[iy] * angles[iz].sin();
        newPoint[iy] = _value[ix] * angles[iz].sin() + _value[iy] * angles[iz].cos();
        ix = Vector3D::indexCycleForward(ix);
        iy = Vector3D::indexCycleForward(iy);
        iz = Vector3D::indexCycleForward(iz);
    }
}

}
