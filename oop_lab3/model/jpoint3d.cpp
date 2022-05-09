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

void Point3D::rotateAround(const Angle& value, int i) noexcept {
    Vector3D newPoint(_value);
    int j = Vector3D::indexCycleForward(i);
    int k = Vector3D::indexCycleForward(j);
    newPoint[j] = _value[j] * value.cos() - _value[k] * value.sin();
    newPoint[k] = _value[j] * value.sin() + _value[k] * value.cos();
}

std::ostream& Point3D::addToStream(std::ostream& stream) const {
    return stream << "Point" << _value;
}

std::wostream& Point3D::addToStream(std::wostream& stream) const {
    return stream << L"Point" << _value;
}

}
