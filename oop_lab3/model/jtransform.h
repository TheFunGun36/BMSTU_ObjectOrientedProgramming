#pragma once
#include "jvector3d.h"
#include "jeulerangles.h"

namespace Jora {

class Transform : public Printable {
public:
    Transform(const Transform& other);
    Transform(Vector3D position = Vector3D(), EulerAngles rotation = EulerAngles(), Vector3D scale = Vector3D());

    inline const Vector3D& position() const { return _position; }
    inline Vector3D& position() { return _position; }
    inline void setPosition(const Vector3D& value) { _position = value; }

    inline const EulerAngles& rotation() const { return _rotation; }
    inline EulerAngles& rotation() { return _rotation; }
    inline void setPosition(const EulerAngles& value) { _rotation = value; }

    inline const Vector3D& scale() const { return _scale; }
    inline Vector3D& scale() { return _scale; }
    inline void setScale(const Vector3D& value) { _scale = value; }

    Vector3D pointGlobalToLocal(const Vector3D& point);
    Vector3D pointLocalToGlobal(const Vector3D& point);

private:
    Vector3D _position;
    EulerAngles _rotation;
    Vector3D _scale;
};

}
