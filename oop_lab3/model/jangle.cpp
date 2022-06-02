#include "pch.h"
#include "jangle.h"
#include <cmath>

namespace Jora {

Angle::Angle()
    : _radians(0.)
    , _sin(0.)
    , _cos(1.) {}

Angle Angle::fromDegrees(real value) {
    Angle a;
    a.setDegrees(value);
    return a;
}

Angle Angle::fromRadians(real value) {
    Angle a;
    a.setRadians(value);
    return a;
}

real Angle::degreesFromRadians(real value) {
    return value * 180 / M_PI;
}

real Angle::radiansFromDegrees(real value) {
    return value * M_PI / 180;
}

real Angle::optimizeDegrees(real value) {
    return fmod(value, 360.) + 360. * (value < 0.);
}

real Angle::optimizeRadians(real value) {
    constexpr real pi2 = M_PI * 2;
    return fmod(value, pi2) + pi2 * (value < 0.);
}

real Angle::degrees() const {
    return degreesFromRadians(_radians);
}

real Angle::radians() const {
    return _radians;
}

void Angle::setDegrees(const real& value) {
    _radians = optimizeRadians(radiansFromDegrees(value));
    _sin = std::sin(_radians);
    _cos = std::cos(_radians);
}

void Angle::setRadians(const real& value) {
    _radians = optimizeRadians(value);
    _sin = std::sin(_radians);
    _cos = std::cos(_radians);
}

real Angle::cos() const {
    return _cos;
}

real Angle::sin() const {
    return _sin;
}

bool Angle::operator==(const Angle& other) const {
    return realEq(_radians, other._radians);
}

bool Angle::operator!=(const Angle& other) const {
    return !(*this == other);
}

Angle& Angle::operator=(const Angle& other) {
    _radians = other._radians;
    _cos = other._cos;
    _sin = other._sin;
    return *this;
}

Angle& Angle::operator+=(const Angle& other) {
    setRadians(_radians + other._radians);
    return *this;
}

Angle& Angle::operator-=(const Angle& other) {
    setRadians(_radians - other._radians);
    return *this;
}

Angle& Angle::operator*=(real value) {
    setRadians(_radians * value);
    return *this;
}

Angle& Angle::operator/=(real value) {
    setRadians(_radians / value);
    return *this;
}

Angle Angle::operator+(const Angle& other) const {
    Angle copy(*this);
    copy += other;
    return copy;
}

Angle Angle::operator-(const Angle& other) const {
    Angle copy(*this);
    copy -= other;
    return copy;
}

Angle Angle::operator*(real value) const {
    Angle copy(*this);
    copy *= value;
    return copy;
}

Angle Angle::operator/(real value) const {
    Angle copy(*this);
    copy /= value;
    return copy;
}

std::ostream& Angle::addToStream(std::ostream& stream) const {
    return stream << "radians(" << radians() << ")";
}

std::wostream& Angle::addToStream(std::wostream& stream) const {
    return stream << L"radians(" << radians() << L")";
}

}
