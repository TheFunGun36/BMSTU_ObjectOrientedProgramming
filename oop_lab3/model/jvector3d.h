#pragma once
#include <initializer_list>
#include <array>
#include "jreal.h"
#include "jcoords3dexception.h"
#include "jprintable.h"

namespace Jora {

enum class Axis
{
    X,
    Y,
    Z
};

class Vector3D : public Printable {
public:
    Vector3D(real x = 0., real y = 0., real z = 0.) noexcept;
    Vector3D(const Vector3D& other) = default;
    virtual ~Vector3D() = default;

    virtual real operator[](size_t index) const;
    virtual real& operator[](size_t index);
    virtual real operator[](Axis axis) const;
    virtual real& operator[](Axis axis);
    virtual real x() const noexcept;
    virtual real y() const noexcept;
    virtual real z() const noexcept;
    virtual real& x() noexcept;
    virtual real& y() noexcept;
    virtual real& z() noexcept;
    virtual Vector3D& setX(real value) noexcept;
    virtual Vector3D& setY(real value) noexcept;
    virtual Vector3D& setZ(real value) noexcept;

    virtual Vector3D& operator=(const Vector3D& other) noexcept;

    virtual Vector3D& operator+=(const Vector3D& other) noexcept;
    virtual Vector3D& operator+=(real value) noexcept;
    virtual Vector3D& operator-=(const Vector3D& other) noexcept;
    virtual Vector3D& operator-=(real value) noexcept;
    virtual Vector3D& operator*=(real value) noexcept;
    virtual Vector3D& operator/=(real value) noexcept;

    virtual Vector3D operator+(const Vector3D& other) const noexcept;
    virtual Vector3D operator+(real value) const noexcept;
    virtual Vector3D operator-(const Vector3D& other) const noexcept;
    virtual Vector3D operator-(real value) const noexcept;
    virtual Vector3D operator*(real value) const noexcept;
    virtual Vector3D operator/(real value) const noexcept;

    virtual Vector3D operator-() const noexcept;

    virtual bool operator==(const Vector3D& other) const noexcept;
    virtual bool operator!=(const Vector3D& other) const noexcept;
    virtual operator bool();

    static Axis nextAxis(Axis axis);
    static Axis prevAxis(Axis axis);
    static int nextAxis(int axis);
    static int prevAxis(int axis);

protected:
    virtual std::ostream& addToStream(std::ostream& stream) const override;
    virtual std::wostream& addToStream(std::wostream& stream) const override;

private:
    std::array<real, 3> _value;
};

}
