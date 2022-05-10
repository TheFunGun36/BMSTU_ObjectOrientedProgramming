#pragma once
#include "jpixmapbase.h"

namespace Jora {

class WindowBase : public Printable {
public:
    inline virtual const PixmapBase& pixmap() const noexcept {
        return const_cast<WindowBase&>(*this).pixmap();
    }
    virtual PixmapBase& pixmap() noexcept = 0;
    virtual void setPixmap(const PixmapBase& pixmap) noexcept = 0;

    virtual void eventMouseMove()

protected:
    WindowBase() = default;
    WindowBase(const WindowBase& other) = delete;
    WindowBase& operator=(const WindowBase& other) = delete;
};

}
