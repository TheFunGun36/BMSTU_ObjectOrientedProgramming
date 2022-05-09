#pragma once
#include "jvector3d.h"
#include "jangle.h"

namespace Jora {

class Object3D : public Printable {
public:
    virtual void move(const Vector3D& offset) noexcept = 0;
    virtual void scale(const Vector3D& factors) = 0;
    virtual void rotate(const Angle& x, const Angle& y, const Angle& z) noexcept;
    virtual void rotateAround(const Angle& value, Axis axisIndex) noexcept = 0;
    inline virtual ~Object3D() = default;
};

}
