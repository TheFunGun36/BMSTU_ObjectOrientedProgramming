#pragma once
#include "jmodel3dexception.h"
#include "jsceneobject.h"
#include <vector>
#include <string>

namespace Jora {

class Model3D : public SceneObject {
public:
    Model3D(const std::string& label);
    explicit Model3D(const Model3D& other) = default;
    Model3D(Model3D&& other) noexcept;
    virtual ~Model3D() = default;

    virtual bool addPoint(const Vector3D& point) noexcept;
    virtual Vector3D& point(int index);
    virtual const Vector3D& point(int index) const;
    virtual size_t pointsAmount() const noexcept;

    virtual operator bool() const noexcept;
    virtual bool isEmpty() const noexcept;
    virtual bool isValid() const noexcept = 0;

    virtual Model3D &operator<<(const Vector3D& point);

private:
    virtual std::ostream& addToStream(std::ostream& stream) const override = 0;
    virtual std::wostream& addToStream(std::wostream& stream) const override = 0;

    std::vector<Vector3D> _points;
};

}
