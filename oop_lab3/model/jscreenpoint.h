#pragma once
#include "jprintable.h"

namespace Jora {

class ScreenPoint : public Printable {
public:
    inline ScreenPoint(int x = 0, int y = 0) noexcept : _x(x), _y(y) {}
    inline ScreenPoint(const ScreenPoint& other) = default;

    inline int x() const noexcept { return _x; }
    inline int y() const noexcept { return _y; }
    inline int operator[](int index) const noexcept { return index ? _y : _x; }

    inline int &x() noexcept { return _x; }
    inline int &y() noexcept { return _y; }
    inline int& operator[](int index) noexcept { return index ? _y : _x; }

    inline void setX(int value) noexcept { _x = value; }
    inline void setY(int value) noexcept { _y = value; }

    ScreenPoint& operator+=(const ScreenPoint& other) noexcept;
    ScreenPoint& operator-=(const ScreenPoint& other) noexcept;

    ScreenPoint& operator+=(int value) noexcept;
    ScreenPoint& operator-=(int value) noexcept;
    ScreenPoint& operator*=(int value) noexcept;
    ScreenPoint& operator/=(int value) noexcept;

    ScreenPoint operator+(const ScreenPoint& other) const noexcept;
    ScreenPoint operator-(const ScreenPoint& other) const noexcept;

    ScreenPoint operator+(int value) const noexcept;
    ScreenPoint operator-(int value) const noexcept;
    ScreenPoint operator*(int value) const noexcept;
    ScreenPoint operator/(int value) const noexcept;

    ScreenPoint operator-();

    inline static int nextAxis(int axis) { return !axis; }

protected:
    virtual std::ostream& addToStream(std::ostream& stream) const override;
    virtual std::wostream& addToStream(std::wostream& stream) const override;

private:
    int _x;
    int _y;
};

}
