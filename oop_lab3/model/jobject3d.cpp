#include "pch.h"
#include "jobject3d.h"

void Jora::Object3D::rotate(const Angle& x, const Angle& y, const Angle& z) noexcept
{
    rotateAround(x, Axis::X);
    rotateAround(y, Axis::Y);
    rotateAround(z, Axis::Z);
}
