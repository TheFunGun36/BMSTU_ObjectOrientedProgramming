#include "pch.h"
#include "jobject3d.h"

void Jora::Object3D::rotate(const Angle& x, const Angle& y, const Angle& z) noexcept {
    rotateAround(x, 0);
    rotateAround(y, 1);
    rotateAround(z, 2);
}
