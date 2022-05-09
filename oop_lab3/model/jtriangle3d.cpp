#include "pch.h"
#include "jtriangle3d.h"

namespace Jora {

Triangle3D::Triangle3D()
    : _indexes({ -1, -1, -1 })
    , _points() {
}

Triangle3D::Triangle3D(const std::weak_ptr<std::vector<Point3D>>& points)
    : _indexes({ -1, -1, -1 })
    , _points(points) {
}

Triangle3D& Triangle3D::operator=(const Triangle3D& other) {
    _points = other._points;
    _indexes = other._indexes;
}

Triangle3D::operator bool() const noexcept {
    return isValid();
}

bool Triangle3D::isValid() const noexcept {
    return !_points.expired() && _indexes[0] >= 0 && _indexes[1] >= 0 && _indexes[2] >= 0;
}

int Triangle3D::index(int which) const noexcept {
    return _indexes[which];
}

void Triangle3D::setIndex(int which, int value) noexcept {
    _indexes[which] = value;
}

void Triangle3D::setIndexes(int point1, int point2, int point3) {
    _indexes = { point1, point2, point3 };
}

const Point3D& Triangle3D::point(int which) const {
    return (*lock())[_indexes[which]];
}

Point3D& Triangle3D::point(int which) {
    return (*lock())[_indexes[which]];
}

const Point3D& Triangle3D::operator[](int which) const {
    return point(which);
}

Point3D& Triangle3D::operator[](int which) {
    return point(which);
}

void Triangle3D::setPoints(const std::weak_ptr<std::vector<Point3D>>& points) noexcept {
    _points = points;
}

std::ostream& Triangle3D::addToStream(std::ostream& stream) const {
    stream << "Triangle3D(";
    if (_points.expired()) {
        stream << "invalid";
    }
    else {
        const auto& points_ptr = _points.lock();
        const auto& points = *points_ptr;

        for (int i = 0; i < points.size(); i++) {
            stream << _indexes[i];
            if (_indexes[i] >= 0 && _indexes[i] < points.size())
                stream << "=" << points[i];
            if (i < points.size() - 1)
                stream << ", ";
        }
    }
    return stream << ")";
}

std::wostream& Triangle3D::addToStream(std::wostream& stream) const {
    stream << L"Triangle3D(";
    if (_points.expired()) {
        stream << L"invalid";
    }
    else {
        const auto& points_ptr = _points.lock();
        const auto& points = *points_ptr;

        for (int i = 0; i < points.size(); i++) {
            stream << _indexes[i];
            if (_indexes[i] >= 0 && _indexes[i] < points.size())
                stream << L"=" << points[i];
            if (i < points.size() - 1)
                stream << L", ";
        }
    }
    return stream << L")";
}

std::shared_ptr<std::vector<Point3D>> Triangle3D::lock() const {
    if (!isValid())
        throw PointsArrayExpired(__FILE__, __FUNCTION__, __LINE__);
    return _points.lock();

}

}