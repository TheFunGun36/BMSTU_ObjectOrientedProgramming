#pragma once
#include "jcommand.h"
#include "jmodelviewer.h"
#include "jscenemanager.h"

namespace Jora {

class CSceneObjectIterate : public Command {
public:
    using SceneObjectPtr = std::weak_ptr<SceneObject>;
    using CompositeRef = const Composite&;
    using Method = void(SceneManager::*)(SceneObjectPtr, CompositeRef);

protected:
    CSceneObjectIterate(const SceneObjectPtr& sceneObject, Method method)
        : _sceneObject(sceneObject), _method(method) {
    }

private:
    virtual inline void execute(Composite& scene, ModelViewer& modelViewer) override {
        (dynamic_cast<SceneManager&>(modelViewer.manager(typeid(SceneManager))).*_method)(_sceneObject, scene);
    }

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

protected:
    CSceneObjectsCount(const IntPtr& value)
        : _value(value), _method(&SceneManager::countSceneObjects) {
    }

private:
    virtual inline void execute(Composite& scene, ModelViewer& modelViewer) override {
        (dynamic_cast<SceneManager&>(modelViewer.manager(typeid(SceneManager))).*_method)(*_value.lock());
    }

    IntPtr _value;
    Method _method;
};
}
