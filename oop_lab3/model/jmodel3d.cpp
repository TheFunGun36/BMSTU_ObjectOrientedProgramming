#include "pch.h"
#include "jmodel3d.h"

namespace Jora {

Model3D::Model3D(const ImplPtr& implementation, const std::string& _label)
    : SceneObject(_label)
    , _implementation(implementation) {
}

Model3D::Model3D(const std::string& _label)
    : SceneObject(_label)
    , _implementation(nullptr) {
}

Model3D::Model3D(Model3D&& other) noexcept
    : SceneObject(other.label())
    , _implementation(other._implementation) {
    other._implementation = nullptr;
}

Model3D::operator bool() const noexcept {
    return isValid();
}

bool Model3D::isValid() const noexcept {
    return _implementation && _implementation->isValid();
}

Model3D::ImplPtr Model3D::implementation() noexcept {
    return _implementation;
}

void Model3D::setImplementation(const ImplPtr& implementation) noexcept {
    if (implementation != nullptr)
        _implementation = implementation;
}


std::ostream& Model3D::addToStream(std::ostream& stream) const {
    return stream << "Model3D(id=" << id() << ")";
}

std::wostream& Model3D::addToStream(std::wostream& stream) const {
    return stream << L"Model3D(id=" << id() << L")";
}

}
