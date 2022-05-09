#pragma once
#include <cctype>
#include "jprintable.h"
#include "jreal.h"

namespace Jora {

class Color : public Printable {
public:
    Color() = default;
    Color(const Color& other) = default;
    inline Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255)
        : _r(r), _g(g), _b(b), _a(a) {
    }
    inline Color(real r, real g, real b, real a = 1.0)
        : _r(mapComponent(r))
        , _g(mapComponent(g))
        , _b(mapComponent(b))
        , _a(mapComponent(a)) {
    }

    inline uint8_t red() const noexcept { return _r; }
    inline uint8_t green() const noexcept { return _g; }
    inline uint8_t blue() const noexcept { return _b; }
    inline uint8_t alpha() const noexcept { return _a; }

    inline uint8_t& red() noexcept { return _r; }
    inline uint8_t& green() noexcept { return _g; }
    inline uint8_t& blue() noexcept { return _b; }
    inline uint8_t& alpha() noexcept { return _a; }

    inline uint8_t& setRed(uint8_t value) noexcept { _r = value; }
    inline uint8_t& setGreen(uint8_t value) noexcept { _g = value; }
    inline uint8_t& setBlue(uint8_t value) noexcept { _b = value; }
    inline uint8_t& setAlpha(uint8_t value) noexcept { _a = value; }

    inline uint8_t& setRed(real value) noexcept { _r = mapComponent(value); }
    inline uint8_t& setGreen(real value) noexcept { _g = mapComponent(value); }
    inline uint8_t& setBlue(real value) noexcept { _b = mapComponent(value); }
    inline uint8_t& setAlpha(real value) noexcept { _a = mapComponent(value); }

    inline static float mapComponent(uint8_t value) noexcept { return value / 255.0; }
    inline static uint8_t mapComponent(real value) noexcept { return value * 255; }

    inline static Color blend(Color a, Color b, real r = 0.5) { return a * r + b * (1 - r); };

protected:
    inline virtual std::ostream& addToStream(std::ostream& stream) const override {
        return stream << "Color(" << int(_r) << ", " << int(_g) << ", " << int(_b) << ")";
    }
    inline virtual std::wostream& addToStream(std::wostream& stream) const override {
        return stream << L"Color(" << int(_r) << L", " << int(_g) << L", " << int(_b) << L")";
    }

private:
    uint8_t _r;
    uint8_t _g;
    uint8_t _b;
    uint8_t _a;

    inline Color operator*(real value) {
        _r *= value;
        _g *= value;
        _b *= value;
        _a *= value;
    }
    inline Color operator+(const Color& other) {
        _r += other._r;
        _g += other._g;
        _b += other._b;
        _a += other._a;
    }
};

}
