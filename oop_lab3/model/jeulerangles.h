#pragma once
#include "jangle.h"
#include "property.h"
#include "jvector3d.h"
#include <array>

namespace Jora {

class EulerAngles : public Printable {
public:
    inline EulerAngles(const Angle x = Angle(), const Angle y = Angle(), const Angle z = Angle());
    inline EulerAngles(const EulerAngles& other) = default;

    inline Angle& operator[](int index) { return _angle[index]; }
    inline const Angle& operator[](int index) const { return _angle[index]; }

    inline const Angle& x() const { return _angle[0]; }
    inline Angle& x() { return _angle[0]; }
    inline void setX(const Angle& value) { this->_angle[0] = value; }
    inline const Angle& y() const { return _angle[1]; }
    inline Angle& y() { return _angle[1]; }
    inline void setY(const Angle& value) { this->_angle[1] = value; }
    inline const Angle& z() const { return _angle[2]; }
    inline Angle& z() { return _angle[2]; }
    inline void setZ(const Angle& value) { this->_angle[2] = value; }

    EulerAngles& operator+=(const Angle& other);
    EulerAngles& operator-=(const Angle& other);
    EulerAngles& operator*=(real value);
    EulerAngles& operator/=(real value);

    EulerAngles& operator+=(const EulerAngles& other);
    EulerAngles& operator-=(const EulerAngles& other);
    EulerAngles& operator*=(const Vector3D& value);
    EulerAngles& operator/=(const Vector3D& value);

    EulerAngles operator+(const Angle& other) const;
    EulerAngles operator-(const Angle& other) const;
    EulerAngles operator*(real value) const;
    EulerAngles operator/(real value) const;

    EulerAngles operator+(const EulerAngles& other) const;
    EulerAngles operator-(const EulerAngles& other) const;
    EulerAngles operator*(const Vector3D& value) const;
    EulerAngles operator/(const Vector3D& value) const;

protected:
    virtual std::ostream& addToStream(std::ostream& stream) const;
    virtual std::wostream& addToStream(std::wostream& stream) const;

private:
    std::array<Angle, 3> _angle;
};

}
