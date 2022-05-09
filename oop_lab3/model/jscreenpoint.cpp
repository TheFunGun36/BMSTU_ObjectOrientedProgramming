#include "pch.h"
#include "jscreenpoint.h"

namespace Jora {

ScreenPoint& ScreenPoint::operator+=(const ScreenPoint& other) noexcept {
    _x += other._x;
    _y += other._y;
    return *this;
}

ScreenPoint& ScreenPoint::operator-=(const ScreenPoint& other) noexcept {
    _x -= other._x;
    _y -= other._y;
    return *this;
}

ScreenPoint& ScreenPoint::operator+=(int value) noexcept {
    _x += value;
    _y += value;
    return *this;
}

ScreenPoint& ScreenPoint::operator-=(int value) noexcept {
    _x -= value;
    _y -= value;
    return *this;
}

ScreenPoint& ScreenPoint::operator*=(int value) noexcept {
    _x *= value;
    _y *= value;
    return *this;
}

ScreenPoint& ScreenPoint::operator/=(int value) noexcept {
    _x /= value;
    _y /= value;
    return *this;
}

ScreenPoint ScreenPoint::operator+(const ScreenPoint& other) const noexcept {
    ScreenPoint point(*this);
    point += other;
    return point;
}

ScreenPoint ScreenPoint::operator-(const ScreenPoint& other) const noexcept {
    ScreenPoint point(*this);
    point -= other;
    return point;
}

ScreenPoint ScreenPoint::operator+(int value) const noexcept {
    ScreenPoint point(*this);
    point += value;
    return point;
}

ScreenPoint ScreenPoint::operator-(int value) const noexcept {
    ScreenPoint point(*this);
    point -= value;
    return point;
}

ScreenPoint ScreenPoint::operator*(int value) const noexcept {
    ScreenPoint point(*this);
    point *= value;
    return point;
}

ScreenPoint ScreenPoint::operator/(int value) const noexcept {
    ScreenPoint point(*this);
    point /= value;
    return point;
}

ScreenPoint ScreenPoint::operator-() {
    ScreenPoint p(*this);
    p._x = -p._x;
    p._y = -p._y;
    return p;
}

std::ostream& ScreenPoint::addToStream(std::ostream& stream) const {
    return stream << "(" << _x << ", " << _y << ")";
}

std::wostream& ScreenPoint::addToStream(std::wostream& stream) const {
    return stream << L"(" << _x << L", " << _y << L")";
}

}
