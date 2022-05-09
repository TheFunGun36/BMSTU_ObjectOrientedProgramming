#include "pch.h"
#include "jpoint3d.h"

namespace Jora {

Point3D::Point3D(const Vector3D& value)
    : _value(value) {}

const Vector3D& Point3D::value() const noexcept {
    return _value;
}

Vector3D& Point3D::value() noexcept {
    return _value;
}

void Point3D::setValue(const Vector3D& point) noexcept {
    _value = point;
}

void Point3D::scale(const Vector3D& factors) noexcept {
    for (int i = 0; i < 3; i++)
        _value[i] *= factors[i];
}

void Point3D::rotateAround(const Angle& value, Axis axis) noexcept {
    Vector3D newPoint(_value);
    int i = int(axis);
    int j = int(Vector3D::nextAxis(axis));
    int k = int(Vector3D::prevAxis(axis));
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
