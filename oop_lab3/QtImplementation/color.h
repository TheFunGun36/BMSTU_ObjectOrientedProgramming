#pragma once
#include "jcolorbase.h"
#include <qcolor.h>

class Color : public Jora::ColorBase {
public:
    Color() = default;
    Color(const Color& other) noexcept;
    Color& operator=(const Color & other) = default;

    Color(Color&& other) noexcept;
    Color(const QColor& color) noexcept;
    Color(const Jora::ColorBase& other) noexcept;

    inline operator QColor() { return _value; }

    virtual uint8_t red() const noexcept override;
    virtual uint8_t green() const noexcept override;
    virtual uint8_t blue() const noexcept override;
    virtual uint8_t alpha() const noexcept override;

    virtual void setRed(uint8_t value) noexcept override;
    virtual void setGreen(uint8_t value) noexcept override;
    virtual void setBlue(uint8_t value) noexcept override;
    virtual void setAlpha(uint8_t value) noexcept override;

    virtual std::unique_ptr<ColorBase> copy() const override;

protected:
    virtual std::ostream& addToStream(std::ostream& stream) const override;
    virtual std::wostream& addToStream(std::wostream& stream) const override;

private:
    QColor _value;
};
