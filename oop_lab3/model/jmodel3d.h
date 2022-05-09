#pragma once
#include "jtriangle3d.h"
#include "jmodel3dexception.h"

namespace Jora {

class Model3D : public Object3D {
public:
    Model3D();
    explicit Model3D(const Model3D& other);
    Model3D(Model3D&& other) noexcept;
    virtual ~Model3D() = default;

    virtual void move(const Vector3D& offset) noexcept override;
    virtual void scale(const Vector3D& factors) noexcept override;
    virtual void rotateAround(const Angle& value, Axis axisIndex) noexcept override;

    virtual bool addPoint(const Point3D& point) noexcept;
    virtual Point3D& point(int index);
    virtual const Point3D& point(int index) const;
    virtual size_t pointsAmount() const noexcept;

    virtual bool addTriangle(int i1, int i2, int i3) noexcept;
    virtual bool addTriangle(Triangle3D triangle) noexcept;
    virtual Triangle3D& triangle(int index);
    virtual const Triangle3D& triangle(int index) const;
    virtual size_t triangleAmount() const noexcept;

    virtual operator bool() const noexcept;
    virtual bool isEmpty() const noexcept;
    virtual bool isValid() const noexcept;

    virtual Model3D &operator<<(const Point3D& point);
    virtual Model3D &operator<<(const Triangle3D& point);

private:
    virtual std::ostream& addToStream(std::ostream& stream) const override;
    virtual std::wostream& addToStream(std::wostream& stream) const override;

private:
    Point3D _pivot;
    std::shared_ptr<std::vector<Point3D>> _points;
    std::vector<Triangle3D> _triangles;
};

}
