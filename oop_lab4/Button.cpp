#include "Button.h"

Button::Button(int floorIndex, bool isInside, QObject* parent)
    : QObject(parent)
    , _isInside(isInside)
    , _floorIndex(floorIndex)
    {
    connect(this, &Button::pressed, this, &Button::release);
}

void Button::press() {
    _state = State::Pressed;
    emit pressed(_floorIndex, _isInside);
}

void Button::release() {
    _state = State::Released;
    emit released(_floorIndex, _isInside);
}
