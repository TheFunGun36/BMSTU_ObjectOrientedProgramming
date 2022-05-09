#include "pch.h"
#include "jmodel3d.h"

namespace Jora {

Model3D::Model3D()
    : _points(std::make_shared<std::vector<Point3D>>()) {
}

Model3D::Model3D(const Model3D& other)
    : _points(std::make_shared<std::vector<Point3D>>(*other._points)) {
}

Model3D::Model3D(Model3D&& other) noexcept
    : _pivot()
    , _points(std::move(other._points))
    , _triangles(std::move(other._triangles)) {
}

void Model3D::move(const Vector3D& offset) noexcept {
    _pivot.move(offset);

    for (int i = 0; i < pointsAmount(); i++)
        (*_points)[i].move(offset);
}

void Model3D::scale(const Vector3D& factors) noexcept {
    _pivot.scale(factors);

    for (int i = 0; i < pointsAmount(); i++)
        (*_points)[i].scale(factors);
}

void Model3D::rotateAround(const Angle& value, Axis axisIndex) noexcept {
    _pivot.rotateAround(value, axisIndex);

    for (int i = 0; i < pointsAmount(); i++)
        (*_points)[i].rotateAround(value, axisIndex);
}

bool Model3D::addPoint(const Point3D& point) noexcept {
    bool result = true;
    try {
        (*_points).push_back(point);
    }
    catch (const std::bad_alloc& e) {
        result = false;
    }
    return result;
}

Point3D& Model3D::point(int index) {
    try {
        return (*_points)[index];
    }
    catch (const std::out_of_range& e) {
        throw ModelOutOfRange(__FILE__, __FUNCTION__, __LINE__);
    }
}

const Point3D& Model3D::point(int index) const {
    return const_cast<Model3D &>(*this).point(index);
}

int Model3D::pointsAmount() const noexcept {
    return (*_points).size();
}

bool Model3D::addTriangle(int i1, int i2, int i3) noexcept {
    bool result = true;
    try {
        Triangle3D triangle(_points);
        triangle.setIndexes(i1, i2, i3);
        _triangles.push_back(triangle);
    }
    catch (const std::bad_alloc& e) {
        result = false;
    }
    return result;
}

bool Model3D::addTriangle(Triangle3D triangle) noexcept {
    triangle.setPoints(_points);
    bool result = true;
    try {
        _triangles.push_back(triangle);
    }
    catch (const std::bad_alloc& e) {
        result = false;
    }
    return result;
}

Triangle3D& Model3D::triangle(int index) {
    try {
        return _triangles[index];
    }
    catch (const std::out_of_range& e) {
        throw ModelOutOfRange(__FILE__, __FUNCTION__, __LINE__);
    }
}

const Triangle3D& Model3D::triangle(int index) const {
    return const_cast<Model3D&>(*this).triangle(index);
}

int Model3D::triangleAmount() const noexcept {
    return _triangles.size();
}

Model3D::operator bool() const noexcept {
    return isEmpty();
}

bool Model3D::isValid() const noexcept {
    bool valid = false;

    for (int i = 0; valid && i < _triangles.size(); i++)
        valid = _triangles[i].isValid();

    return valid;
}

Model3D& Model3D::operator<<(const Point3D& point) {
    if (!addPoint(point))
        throw ModelBadAlloc(__FILE__, __FUNCTION__, __LINE__);
    return *this;
}

Model3D& Model3D::operator<<(const Triangle3D& point) {
    if (!addTriangle(point))
        throw ModelBadAlloc(__FILE__, __FUNCTION__, __LINE__);
    return *this;
}

std::ostream& Model3D::addToStream(std::ostream& stream) const {
    stream << "Model3D {";
    if (!_points->empty() || !_triangles.empty())
        stream << '\n';
    if (!_points->empty()) {
        stream << "\tPoints:\n";
        for (int i = 0; i < _points->size(); i++)
            stream << "\t\t" << (*_points)[i] << '\n';
    }
    if (!_triangles.empty()) {
        stream << "\tTriangles:\n";
        for (int i = 0; i < _triangles.size(); i++)
            stream << "\t\t" << _triangles[i] << '\n';
    }
    return stream << "}";
}

std::wostream& Model3D::addToStream(std::wostream& stream) const {
    stream << L"Model3D {";
    if (!_points->empty() || !_triangles.empty())
        stream << L'\n';
    if (!_points->empty()) {
        stream << L"\tPoints:\n";
        for (int i = 0; i < _points->size(); i++)
            stream << L"\t\t" << (*_points)[i] << L'\n';
    }
    if (!_triangles.empty()) {
        stream << L"\tTriangles:\n";
        for (int i = 0; i < _triangles.size(); i++)
            stream << L"\t\t" << _triangles[i] << L'\n';
    }
    return stream << L"}";
}

bool Model3D::isEmpty() const noexcept {
    return _points->empty();
}

}
