#pragma once
#include "jprintable.h"
#include "jcolor.h"
#include "jscreenline.h"
#include <vector>

namespace Jora {

class PixmapBase : public Printable {
public:
    virtual ~PixmapBase() = default;

    virtual void lock() = 0;
    virtual void unlock() = 0;
    virtual void drawLine(const ScreenLine& line) = 0;
    virtual void drawPoint(const ScreenPoint& point, int radius) = 0;
    virtual void drawEllipse(const ScreenPoint& topLeft, const ScreenPoint& bottomRight) = 0;
    virtual void drawEllipse(const ScreenPoint& center, int rx, int ry) = 0;

    // TODO: add setpen, setbrush etc
    static_assert(false); //hehe
};

}
