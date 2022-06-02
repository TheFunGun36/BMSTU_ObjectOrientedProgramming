#pragma once
#include <cctype>
#include <array>
#include "jprintable.h"
#include "jreal.h"

namespace Jora {

class Color : public Printable {
public:
    inline virtual int r() const noexcept = 0;
    inline virtual int g() const noexcept = 0;
    inline virtual int b() const noexcept = 0;
    inline virtual int a() const noexcept = 0;

    inline virtual uint8_t red() const noexcept = 0;
    inline virtual uint8_t green() const noexcept = 0;
    inline virtual uint8_t blue() const noexcept = 0;
    inline virtual uint8_t alpha() const noexcept = 0;

    virtual void setRed(uint8_t value) noexcept = 0;
    virtual void setGreen(uint8_t value) noexcept = 0;
    virtual void setBlue(uint8_t value) noexcept = 0;
    virtual void setAlpha(uint8_t value) noexcept = 0;

    inline virtual void setRed(real value) noexcept { return setRed(Color::mapComponent(value)); }
    inline virtual void setGreen(real value) noexcept { return setGreen(Color::mapComponent(value)); }
    inline virtual void setBlue(real value) noexcept { return setBlue(Color::mapComponent(value)); }
    inline virtual void setAlpha(real value) noexcept { return setAlpha(Color::mapComponent(value)); }

    virtual std::unique_ptr<Color> copy() const = 0;

    inline static real mapComponent(uint8_t value) noexcept { return value / 255.0; }
    inline static uint8_t mapComponent(real value) noexcept { return uint8_t(value * 255); }

protected:
    Color() = default;
    Color(const Color& other) noexcept {
        setRed(other.red());
        setGreen(other.green());
        setBlue(other.blue());
        setAlpha(other.alpha());
    }
    Color& operator=(const Color& other) = default;
};

}
