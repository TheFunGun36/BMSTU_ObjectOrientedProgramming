#pragma once
#include "jcommand.h"
#include "jrendermanager.h"
#include "jcamera.h"

namespace Jora {

class CSetActiveCamera : public Command {
public:
    using Method = void(RenderManager::*)(const std::weak_ptr<Camera3D>&);

    inline CSetActiveCamera(const std::weak_ptr<Camera3D>& camera)
        : _camera(camera)
        , _method(&RenderManager::setActiveCamera) {
    }
    virtual void execute(Composite& scene, Composite& selection, Manager& manager) override {
        (dynamic_cast<RenderManager&>(manager).*_method)(_camera);
    }
    virtual const std::type_info& neededManager() const noexcept override {
        return typeid(RenderManager);
    }

private:
    std::weak_ptr<Camera3D> _camera;
    Method _method;
};

class CRender : public Command {
public:
    using Method = void(RenderManager::*)(Painter&, const SceneObject&);

    inline CRender(Painter& painter, const SceneObject& target)
        : _painter(painter)
        , _target(target)
        , _method(&RenderManager::render) {
    }
    virtual void execute(Composite& scene, Composite& selection, Manager& manager) override {
        (dynamic_cast<RenderManager&>(manager).*_method)(_painter, _target);
    }
    virtual const std::type_info& neededManager() const noexcept override {
        return typeid(RenderManager);
    }

private:
    Painter& _painter;
    const SceneObject& _target;
    Method _method;
};

}