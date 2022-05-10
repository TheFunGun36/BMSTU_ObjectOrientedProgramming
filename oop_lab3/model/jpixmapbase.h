#pragma once
#include "jprintable.h"
#include "jscreenline.h"
#include "jpainterbase.h"
#include <vector>

namespace Jora {

class PixmapBase : public Printable {
public:
    virtual ~PixmapBase() = default;

    virtual void lock() = 0;
    virtual void unlock() = 0;

    virtual void addLine(const ScreenLine& line) = 0;
    virtual void addPoint(const ScreenPoint& point, int radius) = 0;
    virtual void addEllipse(const ScreenPoint& topLeft, const ScreenPoint& bottomRight) = 0;
    virtual void addEllipse(const ScreenPoint& center, int rx, int ry) = 0;
    virtual void addRectangle(const ScreenPoint& topLeft, const ScreenPoint& bottomRight) = 0;
    virtual void addRectangle(const ScreenPoint& center, int width, int height) = 0;

    virtual size_t width() const noexcept = 0;
    virtual size_t height() const noexcept = 0;
    virtual void resize(size_t width, size_t height) = 0;

protected:
    PixmapBase() = default;
    PixmapBase(const PixmapBase& other) = delete;
    PixmapBase& operator=(const PixmapBase& other) = delete;
};

}
