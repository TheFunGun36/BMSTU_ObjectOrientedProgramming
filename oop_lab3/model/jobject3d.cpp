#include "pch.h"
#include "jobject3d.h"

void Jora::Object3D::rotate(const Angle& x, const Angle& y, const Angle& z) noexcept {
    rotateX(x);
    rotateY(y);
    rotateZ(z);
}
