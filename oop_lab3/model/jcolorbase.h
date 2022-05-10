#pragma once
#include <cctype>
#include "jprintable.h"
#include "jreal.h"

namespace Jora {

class ColorBase : public Printable {
public:

    inline virtual uint8_t red() const noexcept = 0;
    inline virtual uint8_t green() const noexcept = 0;
    inline virtual uint8_t blue() const noexcept = 0;
    inline virtual uint8_t alpha() const noexcept = 0;

    virtual void setRed(uint8_t value) noexcept = 0;
    virtual void setGreen(uint8_t value) noexcept = 0;
    virtual void setBlue(uint8_t value) noexcept = 0;
    virtual void setAlpha(uint8_t value) noexcept = 0;

    inline virtual void setRed(real value) noexcept { return setRed(ColorBase::mapComponent(value)); }
    inline virtual void setGreen(real value) noexcept { return setGreen(ColorBase::mapComponent(value)); }
    inline virtual void setBlue(real value) noexcept { return setBlue(ColorBase::mapComponent(value)); }
    inline virtual void setAlpha(real value) noexcept { return setAlpha(ColorBase::mapComponent(value)); }

    virtual std::unique_ptr<ColorBase> copy() const = 0;

    inline static real mapComponent(uint8_t value) noexcept { return value / 255.0; }
    inline static uint8_t mapComponent(real value) noexcept { return value * 255; }

protected:
    ColorBase() = default;
    ColorBase(const ColorBase& other) noexcept {
        setRed(other.red());
        setGreen(other.green());
        setBlue(other.blue());
        setAlpha(other.alpha());
    }
    ColorBase& operator=(const ColorBase& other) = default;
};

}
