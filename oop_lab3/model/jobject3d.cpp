#include "pch.h"
#include "jsceneobject.h"

void Jora::SceneObject::rotate(const Angle& x, const Angle& y, const Angle& z) noexcept
{
    rotateAround(x, Axis::X);
    rotateAround(y, Axis::Y);
    rotateAround(z, Axis::Z);
}
