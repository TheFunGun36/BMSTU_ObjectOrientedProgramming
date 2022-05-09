#pragma once
#include <vector>
#include "jpoint3d.h"
#include "jtriangle3dexception.h"

namespace Jora {

class Triangle3D : public Object3D {
public:
    Triangle3D();
    Triangle3D(const std::weak_ptr<std::vector<Point3D>>& points);
    Triangle3D(const Triangle3D& other) = default;
    virtual ~Triangle3D() = default;

    virtual Triangle3D& operator=(const Triangle3D& other);

    virtual operator bool() const noexcept;
    virtual bool isValid() const noexcept;

    virtual int index(int which) const noexcept;
    virtual void setIndex(int which, int value) noexcept;
    virtual void setIndexes(int point1, int point2, int point3);

    virtual const Point3D& point(int which) const;
    virtual Point3D& point(int which);
    virtual const Point3D& operator[](int which) const;
    virtual Point3D& operator[](int which);

    virtual void setPoints(const std::weak_ptr<std::vector<Point3D>>& points) noexcept;

    virtual void move(const Vector3D& offset) noexcept override;
    virtual void scale(const Vector3D& factors) noexcept override;
    virtual void rotateAround(const Angle& value, Axis axisIndex) noexcept override;

protected:
    virtual std::ostream& addToStream(std::ostream& stream) const override;
    virtual std::wostream& addToStream(std::wostream& stream) const override;

    virtual std::shared_ptr<std::vector<Point3D>> lock() const;

private:
    std::array<int, 3> _indexes;
    std::weak_ptr<std::vector<Point3D>> _points;
};

}
