#pragma once
#include <initializer_list>
#include <ostream>
#include "jnumerical.h"
#include "jcoords3dexception.h"

namespace Jora {

class Vector3D {
public:
    Vector3D(real x = 0., real y = 0., real z = 0.) noexcept;
    Vector3D(const Vector3D& other) = default;

    real operator[](size_t index) const;
    real& operator[](size_t index);
    real x() const noexcept;
    real y() const noexcept;
    real z() const noexcept;
    real& x() noexcept;
    real& y() noexcept;
    real& z() noexcept;
    Vector3D& setX(real value) noexcept;
    Vector3D& setY(real value) noexcept;
    Vector3D& setZ(real value) noexcept;

    Vector3D& operator=(const Vector3D& other) noexcept;

    Vector3D& operator+=(const Vector3D& other) noexcept;
    Vector3D& operator+=(real value) noexcept;
    Vector3D& operator-=(const Vector3D& other) noexcept;
    Vector3D& operator-=(real value) noexcept;
    Vector3D& operator*=(real value) noexcept;
    Vector3D& operator/=(real value) noexcept;

    Vector3D operator+(const Vector3D& other) const noexcept;
    Vector3D operator+(real value) const noexcept;
    Vector3D operator-(const Vector3D& other) const noexcept;
    Vector3D operator-(real value) const noexcept;
    Vector3D operator*(real value) const noexcept;
    Vector3D operator/(real value) const noexcept;

    Vector3D operator-() const noexcept;

    bool operator==(const Vector3D& other) const noexcept;
    bool operator!=(const Vector3D& other) const noexcept;
    operator bool();

    static size_t indexCycleForward(size_t value);
    static size_t indexCycleBackward(size_t value);

    friend std::ostream& operator<<(std::ostream& stream, const Vector3D& position);
    friend std::wostream& operator<<(std::wostream& stream, const Vector3D& position);

private:
    real _value[3];
};

}
