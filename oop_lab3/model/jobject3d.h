#pragma once
#include "jvector3d.h"
#include "jangle.h"

namespace Jora {

class Object3D {
public:
    virtual void move(const Vector3D& offset) noexcept = 0;
    virtual void scale(const Vector3D& factors) = 0;
    virtual void rotate(const Angle& x, const Angle& y, const Angle& z) noexcept;
    virtual void rotateX(const Angle& value) noexcept = 0;
    virtual void rotateY(const Angle& value) noexcept = 0;
    virtual void rotateZ(const Angle& value) noexcept = 0;

protected:
    Object3D() = default;
    Object3D(const Object3D& other) = default;
};

}
