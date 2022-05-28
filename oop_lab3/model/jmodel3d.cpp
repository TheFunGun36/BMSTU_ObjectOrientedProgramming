#include "pch.h"
#include "jmodel3d.h"

namespace Jora {

Model3D::Model3D(const ImplPtr& implementation, const std::string& _label)
    : SceneObject(_label)
    , _implementation(implementation) {
}

Model3D::Model3D(Model3D&& other) noexcept
    : SceneObject(other.label())
    , _points(std::move(other._points)) {
}

bool Model3D::addPoint(const Vector3D& point) noexcept {
    _points.push_back(point);
    return true;
}

Vector3D& Model3D::point(size_t index) {
    return _points[index];
}

Vector3D& Model3D::operator[](size_t index) {
    return _points[index];
}

const Vector3D& Model3D::point(size_t index) const {
    return const_cast<Model3D &>(*this).point(index);
}

const Vector3D& Model3D::operator[](size_t index) const {
    return _points[index];
}

size_t Model3D::pointsAmount() const noexcept {
    return _points.size();
}

Model3D::operator bool() const noexcept {
    return isEmpty();
}

Model3D& Model3D::operator<<(const Vector3D& point) {
    addPoint(point);
    return *this;
}

std::ostream& Model3D::addToStream(std::ostream& stream) const {
    return stream << "Model3D()";
}

std::wostream& Model3D::addToStream(std::wostream& stream) const {
    return stream << L"Model3D()";
}

bool Model3D::isEmpty() const noexcept {
    return _points.empty();
}

bool Model3D::isValid() const noexcept {
    return _implementation->isValid(_points.size());
}

}
