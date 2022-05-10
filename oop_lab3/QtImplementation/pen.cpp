#include "pen.h"
#include "color.h"

Pen::Pen(const QPen& other) noexcept
    : _value(other) {}

std::unique_ptr<Jora::PenBase> Pen::copy() const {
    return std::make_unique<Jora::PenBase>(*this);
}

std::unique_ptr<Jora::ColorBase> Pen::color() const noexcept {
    return std::make_unique<Color>(_value.color());
}

void Pen::setColor(const Jora::ColorBase& color) noexcept {
    _value.setColor(Color(color));
}
