#pragma once
#include "jmodel3dexception.h"
#include "jsceneobject.h"
#include "jmodel3d_impl.h"
#include <vector>
#include <string>

namespace Jora {

class Model3D : public SceneObject {
public:
    using ImplPtr = std::shared_ptr<Model3DImpl>;

    Model3D(const ImplPtr& implementation, const std::string& label);
    Model3D(const Model3D& other) = delete;
    Model3D(Model3D&& other) noexcept;
    virtual ~Model3D() = default;

    virtual Vector3D& point(size_t index);
    virtual Vector3D& operator[](size_t index);
    virtual const Vector3D& point(size_t index) const;
    virtual const Vector3D& operator[](size_t index) const;
    virtual size_t pointsAmount() const noexcept;

    virtual bool addPoint(const Vector3D& point) noexcept;
    virtual Model3D& operator<<(const Vector3D& point);

    virtual operator bool() const noexcept;
    virtual bool isEmpty() const noexcept;
    virtual bool isValid() const noexcept;

    inline virtual ImplPtr implementation() noexcept { return _implementation; }
    inline virtual const Model3DImpl& implementation() const noexcept { return *_implementation; }

protected:
    ImplPtr _implementation;

private:
    virtual std::ostream& addToStream(std::ostream& stream) const override;
    virtual std::wostream& addToStream(std::wostream& stream) const override;

    std::vector<Vector3D> _points;
};

}
