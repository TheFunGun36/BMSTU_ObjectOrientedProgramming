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
    using ConstImplPtr = std::shared_ptr<const Model3DImpl>;

    Model3D(const ImplPtr& implementation, const std::string& label = "Model");
    Model3D(const std::string& label = "Model");
    Model3D(const Model3D& other) = delete;
    Model3D(Model3D&& other) noexcept;
    virtual ~Model3D() = default;

    virtual operator bool() const noexcept;
    virtual bool isValid() const noexcept;

    virtual ImplPtr implementation() noexcept;
    virtual ConstImplPtr implementation() const noexcept;
    virtual void setImplementation(const ImplPtr& implementation) noexcept;

    virtual void setVisible(const bool& visible) noexcept override;

protected:
    ImplPtr _implementation;

private:
    virtual std::ostream& addToStream(std::ostream& stream) const override;
    virtual std::wostream& addToStream(std::wostream& stream) const override;
};

}
