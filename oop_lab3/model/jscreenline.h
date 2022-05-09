#pragma once
#include "jscreenpoint.h"

namespace Jora {

class ScreenLine : public Printable {
public:
    inline ScreenLine() = default;
    inline ScreenLine(int x1, int y1, int x2, int y2) noexcept
        : _p1(x1, y1), _p2(x2, y2) {
    }
    inline ScreenLine(const ScreenPoint& p1, const ScreenPoint& p2) noexcept
        : _p1(p1), _p2(p2) {
    }

    inline ScreenPoint& p1() noexcept { return _p1; }
    inline ScreenPoint& p2() noexcept { return _p2; }
    inline const ScreenPoint& p1() const noexcept { return _p1; }
    inline const ScreenPoint& p2() const noexcept { return _p2; }
    inline void setP1(const ScreenPoint& value) noexcept { _p1 = value; }
    inline void setP2(const ScreenPoint& value) noexcept { _p2 = value; }

    inline int& x1() noexcept { return _p1.x(); }
    inline int& y1() noexcept { return _p1.y(); }
    inline int& x2() noexcept { return _p2.x(); }
    inline int& y2() noexcept { return _p2.y(); }
    inline int x1() const noexcept { return _p1.x(); }
    inline int y1() const noexcept { return _p1.y(); }
    inline int x2() const noexcept { return _p2.x(); }
    inline int y2() const noexcept { return _p2.y(); }
    inline int setX1(int value) noexcept { _p1.x() = value; }
    inline int setY1(int value) noexcept { _p1.y() = value; }
    inline int setX2(int value) noexcept { _p2.x() = value; }
    inline int setY2(int value) noexcept { _p2.y() = value; }

protected:
    virtual std::ostream& addToStream(std::ostream& stream) const override;
    virtual std::wostream& addToStream(std::wostream& stream) const override;

private:
    ScreenPoint _p1;
    ScreenPoint _p2;
};

}
