#include "jcomposite.h"

namespace Jora {

std::ostream& Composite::addToStream(std::ostream& stream) const {
    stream << "{";
    for (auto it = _list.begin(); it != _list.end();) {
        stream << **it;
        it++;
        if (it != _list.end())
            stream << ", ";
    }
    return stream << "}";
}

std::wostream& Composite::addToStream(std::wostream& stream) const {
    stream << L"{";
    for (auto it = _list.begin(); it != _list.end();) {
        stream << **it;
        it++;
        if (it != _list.end())
            stream << L", ";
    }
    return stream << L"}";
}

}
