#pragma once
#include "jsceneobject.h"

namespace Jora {

class Point3D : public SceneObject {
public:
    Point3D() = default;
    Point3D(const Point3D& other) = default;
    Point3D(const Vector3D& value);

    const Vector3D& value() const noexcept;
    Vector3D& value() noexcept;
    void setValue(const Vector3D& point) noexcept;

protected:
    virtual std::ostream& addToStream(std::ostream& stream) const override;
    virtual std::wostream& addToStream(std::wostream& stream) const override;

private:
    Vector3D _value;
};

}