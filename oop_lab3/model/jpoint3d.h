#pragma once
#include "jobject3d.h"

namespace Jora {

class Point3D : public Object3D {
public:
    Point3D() = default;
    Point3D(const Point3D& other) = default;
    Point3D(const Vector3D& value);

    const Vector3D& value() const;
    Vector3D& value();
    void setValue(const Vector3D& point);
    virtual void scale(const Vector3D& factors) override;
    virtual void rotateAround(const Angle& value, int axisIndex) noexcept override;

protected:
    virtual std::ostream& addToStream(std::ostream& stream) const override;
    virtual std::wostream& addToStream(std::wostream& stream) const override;

private:
    Vector3D _value;
};

}