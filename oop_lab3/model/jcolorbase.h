#pragma once
#include <cctype>
#include "jprintable.h"
#include "jreal.h"

namespace Jora {

class ColorBase : public Printable {
public:
    ColorBase(const ColorBase& other) = delete;
    ColorBase& operator=(const ColorBase& other) = delete;

    inline virtual uint8_t red() const noexcept { return const_cast<ColorBase&>(*this).red(); }
    inline virtual uint8_t green() const noexcept { return const_cast<ColorBase&>(*this).green(); }
    inline virtual uint8_t blue() const noexcept { return const_cast<ColorBase&>(*this).blue(); }
    inline virtual uint8_t alpha() const noexcept { return const_cast<ColorBase&>(*this).alpha(); }

    virtual uint8_t& red() noexcept = 0;
    virtual uint8_t& green() noexcept = 0;
    virtual uint8_t& blue() noexcept = 0;
    virtual uint8_t& alpha() noexcept = 0;

    virtual uint8_t& setRed(uint8_t value) noexcept = 0;
    virtual uint8_t& setGreen(uint8_t value) noexcept = 0;
    virtual uint8_t& setBlue(uint8_t value) noexcept = 0;
    virtual uint8_t& setAlpha(uint8_t value) noexcept = 0;

    inline virtual uint8_t& setRed(real value) noexcept { return setRed(ColorBase::mapComponent(value)); }
    inline virtual uint8_t& setGreen(real value) noexcept { return setGreen(ColorBase::mapComponent(value)); }
    inline virtual uint8_t& setBlue(real value) noexcept { return setBlue(ColorBase::mapComponent(value)); }
    inline virtual uint8_t& setAlpha(real value) noexcept { return setAlpha(ColorBase::mapComponent(value)); }

    virtual std::unique_ptr<ColorBase> copy() const = 0;

    inline static real mapComponent(uint8_t value) noexcept { return value / 255.0; }
    inline static uint8_t mapComponent(real value) noexcept { return value * 255; }

protected:
    ColorBase() = default;
};

}
