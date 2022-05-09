#include "pch.h"
#include "jscreenline.h"

std::ostream& Jora::ScreenLine::addToStream(std::ostream& stream) const {
    return stream << "Line(" << _p1 << ", " << _p2 << ")";
}

std::wostream& Jora::ScreenLine::addToStream(std::wostream& stream) const {
    return stream << L"Line(" << _p1 << L", " << _p2 << L")";
}
