#include "pch.h"
#include "jeulerangles.h"

namespace Jora {

inline EulerAngles::EulerAngles(const Angle x, const Angle y, const Angle z)
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

std::ostream& EulerAngles::addToStream(std::ostream& stream) const {
    return stream << "(" << _angle[0] << ", " << _angle[1] << ", " << _angle[2] << ")";
}

std::wostream& EulerAngles::addToStream(std::wostream& stream) const {
    return stream << L"(" << _angle[0] << L", " << _angle[1] << L", " << _angle[2] << L")";
}

}
