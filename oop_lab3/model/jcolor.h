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

    inline virtual real rf() const noexcept { return mapComponent(r()); }
    inline virtual real gf() const noexcept { return mapComponent(g()); }
    inline virtual real bf() const noexcept { return mapComponent(b()); }
    inline virtual real af() const noexcept { return mapComponent(a()); }

    virtual void setR(int value) noexcept = 0;
    virtual void setG(int value) noexcept = 0;
    virtual void setB(int value) noexcept = 0;
    virtual void setA(int value) noexcept = 0;

    inline virtual void setR(real value) noexcept { return setR(mapComponent(value)); }
    inline virtual void setG(real value) noexcept { return setG(mapComponent(value)); }
    inline virtual void setB(real value) noexcept { return setB(mapComponent(value)); }
    inline virtual void setA(real value) noexcept { return setA(mapComponent(value)); }

    virtual std::unique_ptr<Color> copy() const = 0;

    inline static real mapComponent(int value) noexcept { return value / 255.; }
    inline static int mapComponent(real value) noexcept { return value * 255; }

protected:
    Color() = default;
    Color(const Color& other) = default;
    Color& operator=(const Color& other) = default;
};

}
