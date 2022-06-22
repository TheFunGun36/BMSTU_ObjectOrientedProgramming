#pragma once
#include <list>
#include "jcolor.h"
#include "jscreenline.h"
#include "jscreenpoint.h"
#include "jscreenrect.h"

namespace Jora {

class Painter {
public:
    virtual ~Painter() = default;

    virtual void drawLine(ScreenLine line) = 0;
    virtual void drawRect(ScreenRect rect) = 0;
    virtual void drawPoly(const std::list<ScreenPoint>& verticies) = 0;
    virtual void drawPixel(ScreenPoint pixel) = 0;
    virtual void drawEllipse(ScreenRect ellipse) = 0;
    virtual void drawCircle(ScreenPoint center, int radius) = 0;

    virtual void setOutlineColor(const Color& color) = 0;
    virtual void setOutlineWidth(int value) = 0;

    virtual void setFillColor(const Color& color) = 0;
};

}
