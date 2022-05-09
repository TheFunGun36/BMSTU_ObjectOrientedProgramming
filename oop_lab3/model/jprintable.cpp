#include "pch.h"
#include "jprintable.h"
#include <sstream>

namespace Jora {

std::string Printable::toString() const {
    std::stringstream sstr;
    addToStream(sstr) << '\0';
    return sstr.str();
}
std::wstring Printable::toWString() const {
    std::wstringstream sstr;
    addToStream(sstr) << L'\0';
    return sstr.str();
}

std::ostream& operator<<(std::ostream& stream, const Printable& printable) {
    return printable.addToStream(stream);
}
std::wostream& operator<<(std::wostream& stream, const Printable& printable) {
    return printable.addToStream(stream);
}

}