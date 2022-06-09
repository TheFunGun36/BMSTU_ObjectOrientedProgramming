#include "pch.h"
#include "jcomposite.h"

namespace Jora {

Composite::ElementPtr Composite::operator[](size_t id) noexcept {
    ElementPtr result = nullptr;
    auto iterator = _map.find(id);
    if (iterator != _map.end())
        result = iterator->second;
    return result;
}

bool Composite::isComposite() const noexcept {
    return true;
}

bool Composite::contains(size_t id) const noexcept {
    return _map.find(id) != _map.end();
}

size_t Composite::count() const noexcept {
    return _map.size();
}

Composite::IteratorConst Composite::begin() const noexcept {
    return _map.begin();
}

Composite::IteratorConst Composite::end() const noexcept {
    return _map.end();
}

Composite::IteratorConst Composite::cbegin() const noexcept {
    return _map.cbegin();
}

Composite::IteratorConst Composite::cend() const noexcept {
    return _map.cend();
}

bool Composite::remove(size_t id) noexcept {
    bool result = contains(id);
    if (result)
        _map.erase(id);
    return result;
}

bool Composite::remove(IteratorConst it) noexcept {
    _map.erase(it);
}

Composite::Iterator Composite::begin() noexcept {
    return _map.begin();
}

Composite::Iterator Composite::end() noexcept {
    return _map.end();
}

bool Composite::insert(const ElementPtr& sceneObject) noexcept {
    bool result = sceneObject && contains(sceneObject->id());
    if (result)
        _map[sceneObject->id()] = sceneObject;
    return result;
}

std::ostream& Composite::addToStream(std::ostream& stream) const {
    stream << "{";
    for (IteratorConst it = _map.begin(); it != _map.end();) {
        stream << it->first();
        it++;
        if (it != _map.end())
            stream << ", ";
    }
    return stream << "}";
}

std::wostream& Composite::addToStream(std::wostream& stream) const {
    stream << L"{";
    for (IteratorConst it = _map.begin(); it != _map.end();) {
        stream << it->first();
        it++;
        if (it != _map.end())
            stream << L", ";
    }
    return stream << L"}";
}

}
