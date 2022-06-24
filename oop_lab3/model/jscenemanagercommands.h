#pragma once
#include "jcommand.h"
#include "jmodelviewer.h"
#include "jscenemanager.h"
#include "jtransformaction.h"

namespace Jora {

class CSceneObjectsCount : public Command {
public:
    using Method = void(SceneManager::*)(const Composite&, const std::weak_ptr<size_t>&);

    CSceneObjectsCount(const std::weak_ptr<size_t>& value)
        : _method(&SceneManager::countSceneObjects)
        , _value(value) {
    }

    virtual inline void execute(Composite& scene, Manager& manager) override {
        (dynamic_cast<SceneManager&>(manager).*_method)(scene, _value);
    }

    virtual inline const std::type_info& neededManager() const noexcept override {
        return typeid(SceneManager);
    }

private:
    Method _method;
    std::weak_ptr<size_t> _value;
};

class CMakeGroup : public Command {
public:
    using Method = void(SceneManager::*)(Composite&, const std::weak_ptr<ObjectId>&, std::initializer_list<ObjectId>);

    CMakeGroup(const std::weak_ptr<ObjectId>& groupId, std::initializer_list<ObjectId> objectsId)
        : _method(&SceneManager::makeGroup)
        , _objectsId(std::move(objectsId))
        , _groupId(groupId) {
    }

    virtual inline void execute(Composite& scene, Manager& manager) override {
        (dynamic_cast<SceneManager&>(manager).*_method)(scene, _groupId, std::move(_objectsId));
    }

    virtual inline const std::type_info& neededManager() const noexcept override {
        return typeid(SceneManager);
    }
private:
    Method _method;
    std::initializer_list<ObjectId> _objectsId;
    std::weak_ptr<ObjectId> _groupId;

};

class CGetLabel : public Command {
public:
    using Method = void(SceneManager::*)(const Composite&, const std::weak_ptr<std::string>&, ObjectId);

    CGetLabel(ObjectId id, const std::weak_ptr<std::string>& label) 
        : _method(&SceneManager::getLabel)
        , _id(id)
        , _label(label) { }

    virtual inline void execute(Composite& scene, Manager& manager) override {
        (dynamic_cast<SceneManager&>(manager).*_method)(scene, _label, _id);
    }

    virtual inline const std::type_info& neededManager() const noexcept override {
        return typeid(SceneManager);
    }

private:
    Method _method;
    ObjectId _id;
    const std::weak_ptr<std::string> _label;

};

class CSetLabel : public Command {
public:
    using Method = void(SceneManager::*)(Composite&, ObjectId, std::string&&);

    CSetLabel(ObjectId id, std::string&& label)
        : _method(&SceneManager::setLabel)
        , _id(id)
        , _label(std::move(label)) {
    }

    virtual inline void execute(Composite& scene, Manager& manager) override {
        (dynamic_cast<SceneManager&>(manager).*_method)(scene, _id, std::move(_label));
    }

    virtual inline const std::type_info& neededManager() const noexcept override {
        return typeid(SceneManager);
    }

private:
    Method _method;
    ObjectId _id;
    std::string _label;

};

class CRemoveObject : public Command {
public:
    using Method = void(SceneManager::*)(Composite&, ObjectId);

    CRemoveObject(ObjectId id)
        : _method(&SceneManager::removeObject)
        , _id(id) {
    }

    virtual inline void execute(Composite& scene, Manager& manager) override {
        (dynamic_cast<SceneManager&>(manager).*_method)(scene, _id);
    }

    virtual inline const std::type_info& neededManager() const noexcept override {
        return typeid(SceneManager);
    }
private:
    Method _method;
    ObjectId _id;

};

class CClear : public Command {
public:
    using Method = void(SceneManager::*)(Composite&);

    CClear()
        : _method(&SceneManager::clear) {
    }

    virtual inline void execute(Composite& scene, Manager& manager) override {
        (dynamic_cast<SceneManager&>(manager).*_method)(scene);
    }

    virtual inline const std::type_info& neededManager() const noexcept override {
        return typeid(SceneManager);
    }
private:
    Method _method;

};

class CTransform : public Command {
public:
    using Method = void(SceneManager::*)(Composite&, std::unique_ptr<TransformAction>, ObjectId);

    CTransform(std::unique_ptr<TransformAction> action, ObjectId id)
        : _method(&SceneManager::transform)
        , _action(std::move(action))
        , _id(id) {
    }

    virtual inline void execute(Composite& scene, Manager& manager) override {
        (dynamic_cast<SceneManager&>(manager).*_method)(scene, std::move(_action), _id);
    }

    virtual inline const std::type_info& neededManager() const noexcept override {
        return typeid(SceneManager);
    }
private:
    Method _method;
    std::unique_ptr<TransformAction> _action;
    ObjectId _id;
};

class CGetTransform : public Command {
public:
    using Method = void(SceneManager::*)(const std::shared_ptr<Transform>&, const Composite&, ObjectId);

    CGetTransform(const std::shared_ptr<Transform>& transform, ObjectId id)
        : _method(&SceneManager::getTransform)
        , _transform(transform)
        , _id(id) {
    }

    virtual inline void execute(Composite& scene, Manager& manager) override {
        (dynamic_cast<SceneManager&>(manager).*_method)(_transform, scene, _id);
    }

    virtual inline const std::type_info& neededManager() const noexcept override {
        return typeid(SceneManager);
    }
private:
    Method _method;
    std::shared_ptr<Transform> _transform;
    ObjectId _id;
};

}
