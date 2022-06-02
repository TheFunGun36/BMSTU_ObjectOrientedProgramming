#pragma once
#include "jcommand.h"
#include "jmodelviewer.h"
#include "jscenemanager.h"

namespace Jora {

class CSceneObjectIterate : public Command {
public:
    using SceneObjectPtr = std::weak_ptr<SceneObject>;
    using Method = void(SceneManager::*)(SceneObjectPtr, const Composite&);

    virtual inline void execute(Composite& scene, Composite& selection, Manager& manager) override {
        (dynamic_cast<SceneManager&>(manager).*_method)(_sceneObject, scene);
    }

    virtual inline const std::type_info& neededManager() const noexcept override {
        return typeid(SceneManager);
    }

protected:
    CSceneObjectIterate(const SceneObjectPtr& sceneObject, Method method)
        : _sceneObject(sceneObject)
        , _method(method) {
    }

private:
    SceneObjectPtr _sceneObject;
    Method _method;
};

class CNextSceneObject : public CSceneObjectIterate {
    CNextSceneObject(const SceneObjectPtr& sceneObject)
        : CSceneObjectIterate(sceneObject, &SceneManager::nextSceneObject) {
    }
};

class CPrevSceneObject : public CSceneObjectIterate {
    CPrevSceneObject(const SceneObjectPtr& sceneObject)
        : CSceneObjectIterate(sceneObject, &SceneManager::prevSceneObject) {
    }
};

class CFirstSceneObject : public CSceneObjectIterate {
    CFirstSceneObject(const SceneObjectPtr& sceneObject)
        : CSceneObjectIterate(sceneObject, &SceneManager::firstSceneObject) {
    }
};

class CLastSceneObject : public CSceneObjectIterate {
    CLastSceneObject(const SceneObjectPtr& sceneObject)
        : CSceneObjectIterate(sceneObject, &SceneManager::lastSceneObject) {
    }
};

class CSceneObjectsCount : public Command {
public:
    using IntPtr = std::weak_ptr<int>;
    using Method = void(SceneManager::*)(int&);

    CSceneObjectsCount(const IntPtr& value)
        : _value(value), _method(&SceneManager::countSceneObjects) {
    }

    virtual inline void execute(Composite& scene, Composite& selection, Manager& manager) override {
        (dynamic_cast<SceneManager&>(manager).*_method)(*_value.lock());
    }

    virtual inline const std::type_info& neededManager() const noexcept override {
        return typeid(SceneManager);
    }

private:
    IntPtr _value;
    Method _method;
};
}
