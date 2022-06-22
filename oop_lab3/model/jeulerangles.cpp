#include "pch.h"
#include "jeulerangles.h"

namespace Jora {

EulerAngles::EulerAngles(const Angle x, const Angle y, const Angle z)
    : _angle({ x, y, z }) {
}

EulerAngles& EulerAngles::operator+=(const Angle& other) {
    for (int i = 0; i < 3; i++)
        _angle[i] += other;
    return *this;
}

EulerAngles& EulerAngles::operator-=(const Angle& other) {
    for (int i = 0; i < 3; i++)
        _angle[i] -= other;
    return *this;
}

EulerAngles& EulerAngles::operator*=(real value) {
    for (int i = 0; i < 3; i++)
        _angle[i] *= value;
    return *this;
}

EulerAngles& EulerAngles::operator/=(real value) {
    for (int i = 0; i < 3; i++)
        _angle[i] /= value;
    return *this;
}

EulerAngles& EulerAngles::operator+=(const EulerAngles& other) {
    for (int i = 0; i < 3; i++)
        _angle[i] += other[i];
    return *this;
}

EulerAngles& EulerAngles::operator-=(const EulerAngles& other) {
    for (int i = 0; i < 3; i++)
        _angle[i] -= other[i];
    return *this;
}

EulerAngles& EulerAngles::operator*=(const Vector3D& value) {
    for (int i = 0; i < 3; i++)
        _angle[i] *= value[i];
    return *this;
}

EulerAngles& EulerAngles::operator/=(const Vector3D& value) {
    for (int i = 0; i < 3; i++)
        _angle[i] /= value[i];
    return *this;
}

EulerAngles EulerAngles::operator+(const Angle& other) const {
    EulerAngles copy(*this);
    copy += other;
    return copy;
}

EulerAngles EulerAngles::operator-(const Angle& other) const {
    EulerAngles copy(*this);
    copy -= other;
    return copy;
}

EulerAngles EulerAngles::operator*(real value) const {
    EulerAngles copy(*this);
    copy *= value;
    return copy;
}

EulerAngles EulerAngles::operator/(real value) const {
    EulerAngles copy(*this);
    copy /= value;
    return copy;
}

EulerAngles EulerAngles::operator+(const EulerAngles& other) const {
    EulerAngles copy(*this);
    copy += other;
    return copy;
}

EulerAngles EulerAngles::operator-(const EulerAngles& other) const {
    EulerAngles copy(*this);
    copy -= other;
    return copy;
}

EulerAngles EulerAngles::operator*(const Vector3D& value) const {
    EulerAngles copy(*this);
    copy *= value;
    return copy;
}

EulerAngles EulerAngles::operator/(const Vector3D& value) const {
    EulerAngles copy(*this);
    copy /= value;
    return copy;
}

Vector3D EulerAngles::rotatePoint(Vector3D point) const noexcept {
    Vector3D result = point;

    result.setY(point.y() * x().cos() - point.z() * x().sin());
    result.setZ(point.y() * x().sin() + point.z() * x().cos());
    point = result;

    result.setZ(point.z() * y().cos() - point.x() * y().sin());
    result.setX(point.z() * y().sin() + point.x() * y().cos());
    point = result;

    result.setX(point.x() * z().cos() - point.y() * z().sin());
    result.setY(point.x() * z().sin() + point.y() * z().cos());

    return result;
}

Vector3D EulerAngles::rotatePointReverse(Vector3D point) const noexcept {
    Vector3D result = point;

    result.setX(point.x() * z().cos() - point.y() * z().sin());
    result.setY(point.x() * z().sin() + point.y() * z().cos());
    point = result;

    result.setZ(point.z() * y().cos() - point.x() * y().sin());
    result.setX(point.z() * y().sin() + point.x() * y().cos());
    point = result;

    result.setY(point.y() * x().cos() - point.z() * x().sin());
    result.setZ(point.y() * x().sin() + point.z() * x().cos());

    return result;
}

std::ostream& EulerAngles::addToStream(std::ostream& stream) const {
    return stream << "(" << _angle[0] << ", " << _angle[1] << ", " << _angle[2] << ")";
}

std::wostream& EulerAngles::addToStream(std::wostream& stream) const {
    return stream << L"(" << _angle[0] << L", " << _angle[1] << L", " << _angle[2] << L")";
}

}
