#pragma once
#include "jpenbase.h"
#include "jbrushbase.h"
#include "jpixmapbase.h"
#include "jwindowbase.h"

namespace Jora {

class ViewFactoryBase {
    virtual std::unique_ptr<PenBase> createPen() = 0;
    virtual std::unique_ptr<BrushBase> createBrush() = 0;
    virtual std::unique_ptr<PixmapBase> createPixmap() = 0;
    virtual std::unique_ptr<Painter> createPainter() = 0;
    virtual std::unique_ptr<WindowBase> createWindow() = 0;
};

}