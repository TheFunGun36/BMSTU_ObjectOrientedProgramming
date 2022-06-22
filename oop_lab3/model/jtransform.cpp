#include "pch.h"

namespace Jora {

Vector3D Transform::pointGlobalToLocal(Vector3D point) const noexcept {
    for (int i = 0; i < 3; i++)
        point[i] *= _scale[i];
    point = _rotation.rotatePoint(point);
    point += _position;
    return point;
}

Vector3D Transform::pointLocalToGlobal(Vector3D point) const noexcept {
    point -= _position;
    for (int i = 0; i < 3; i++)
        point[i] /= _scale[i];
    point = _rotation.rotatePointReverse(point);
    return point;
}

}
