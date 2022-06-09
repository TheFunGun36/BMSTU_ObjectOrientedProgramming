#include "pch.h"
#include "jsceneobject.h"

namespace Jora {

SceneObject::SceneObject(const std::string& _label)
    : Visible(this, &Self::visible, &Self::setVisible)
    , Label(this, &Self::label, &Self::setLabel)
    , Type(this, &Self::type)
    , Id(this, &Self::id)
    , _visible(false)
    , _label(_label)
    , _transform() {
    _id = generateId();
}

const bool& SceneObject::visible() const noexcept {
    return _visible;
}

const std::string& SceneObject::label() const noexcept {
    return _label;
}

const std::type_info& SceneObject::type() const noexcept {
    return typeid(*this);
}

const size_t& SceneObject::id() const noexcept {
    return _id;
}

const Transform& SceneObject::transform() const noexcept {
    return _transform;
}

Transform& SceneObject::transform() noexcept {
    return _transform;
}

void SceneObject::setVisible(const bool& _visible) noexcept {
    // beeba! Yaaaay
}

void SceneObject::setLabel(const std::string& label) noexcept {
    _label = label;
}

SceneObject::SelfPtr SceneObject::operator[](size_t id) noexcept {
    return nullptr;
}

bool SceneObject::isComposite() const noexcept {
    return false;
}

bool SceneObject::insert(const SceneObject::SelfPtr& sceneObject) noexcept {
    return false;
}

bool SceneObject::remove(size_t id) noexcept {
    return false;
}

bool SceneObject::remove(SceneObject::IteratorConst it) noexcept {
    return false;
}

bool SceneObject::contains(size_t id) const noexcept {
    return _id == id;
}

size_t SceneObject::count() const noexcept {
    return 1;
}

SceneObject::Iterator SceneObject::begin() noexcept {
    return SceneObject::Iterator();
}

SceneObject::Iterator SceneObject::end() noexcept {
    return SceneObject::Iterator();
}

SceneObject::IteratorConst SceneObject::begin() const noexcept {
    return SceneObject::IteratorConst();
}

SceneObject::IteratorConst SceneObject::end() const noexcept {
    return SceneObject::IteratorConst();
}

SceneObject::IteratorConst SceneObject::cbegin() const noexcept {
    return SceneObject::IteratorConst();
}

SceneObject::IteratorConst SceneObject::cend() const noexcept {
    return SceneObject::IteratorConst();
}

size_t SceneObject::generateId() {
    static size_t id = 0;
    return id++;
}

}