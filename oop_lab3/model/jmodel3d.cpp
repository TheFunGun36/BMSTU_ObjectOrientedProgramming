#include "pch.h"
#include "jmodel3d.h"

namespace Jora {

Model3D::Model3D(const std::string& _label)
    : SceneObject(_label) {
}

Model3D::Model3D(Model3D&& other) noexcept
    : SceneObject(other.label())
    , _points(std::move(other._points)) {
}

bool Model3D::addPoint(const Vector3D& point) noexcept {
    _points.push_back(point);
    return true;
}

Vector3D& Model3D::point(int index) {
    return _points[index];
}

const Vector3D& Model3D::point(int index) const {
    return const_cast<Model3D &>(*this).point(index);
}

size_t Model3D::pointsAmount() const noexcept {
    return _points.size();
}

Model3D::operator bool() const noexcept {
    return isEmpty();
}

Model3D& Model3D::operator<<(const Vector3D& point) {
    if (!addPoint(point))
        throw ModelBadAlloc(__FILE__, __FUNCTION__, __LINE__);
    return *this;
}

//std::ostream& Model3D::addToStream(std::ostream& stream) const {
//    stream << "Model3D {";
//    if (!_points->empty() || !_triangles.empty())
//        stream << '\n';
//    if (!_points->empty()) {
//        stream << "\tPoints:\n";
//        for (int i = 0; i < _points->size(); i++)
//            stream << "\t\t" << (*_points)[i] << '\n';
//    }
//    if (!_triangles.empty()) {
//        stream << "\tTriangles:\n";
//        for (int i = 0; i < _triangles.size(); i++)
//            stream << "\t\t" << _triangles[i] << '\n';
//    }
//    return stream << "}";
//}
//
//std::wostream& Model3D::addToStream(std::wostream& stream) const {
//    stream << L"Model3D {";
//    if (!_points->empty() || !_triangles.empty())
//        stream << L'\n';
//    if (!_points->empty()) {
//        stream << L"\tPoints:\n";
//        for (int i = 0; i < _points->size(); i++)
//            stream << L"\t\t" << (*_points)[i] << L'\n';
//    }
//    if (!_triangles.empty()) {
//        stream << L"\tTriangles:\n";
//        for (int i = 0; i < _triangles.size(); i++)
//            stream << L"\t\t" << _triangles[i] << L'\n';
//    }
//    return stream << L"}";
//}

bool Model3D::isEmpty() const noexcept {
    return _points.empty();
}

}
