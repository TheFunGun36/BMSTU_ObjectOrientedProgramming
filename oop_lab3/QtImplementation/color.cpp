#include "color.h"

Color::Color(const Color& other) noexcept
    : ColorBase()
    , _value(other._value) {}

Color::Color(Color&& other) noexcept
    : _value(std::move(other._value)) {}

Color::Color(const QColor& color) noexcept
    : _value(color) {}

Color::Color(const Jora::ColorBase& other) noexcept
    : ColorBase(other) {}

uint8_t Color::red() const noexcept {
    _value.red();
}

uint8_t Color::green() const noexcept {
    _value.green();
}

uint8_t Color::blue() const noexcept {
    _value.blue();
}

uint8_t Color::alpha() const noexcept {
    _value.alpha();
}

void Color::setRed(uint8_t value) noexcept {
    _value.setRed(value);
}

void Color::setGreen(uint8_t value) noexcept {
    _value.setGreen(value);
}

void Color::setBlue(uint8_t value) noexcept {
    _value.setBlue(value);
}

void Color::setAlpha(uint8_t value) noexcept {
    _value.setAlpha(value);
}

std::unique_ptr<Jora::ColorBase> Color::copy() const {
    return std::make_unique<Color>(*this);
}

std::ostream& Color::addToStream(std::ostream& stream) const {
    return stream << "QColor(" << _value.red() << ", " << _value.green() << ", " << _value.blue() << ")";
}

std::wostream& Color::addToStream(std::wostream& stream) const {
    return stream << L"QColor(" << _value.red() << L", " << _value.green() << L", " << _value.blue() << L")";
}
