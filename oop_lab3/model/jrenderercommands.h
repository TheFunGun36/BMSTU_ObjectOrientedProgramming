#pragma once
#include "jcommand.h"
#include "jrendermanager.h"
#include "jcamera.h"

namespace Jora {

class CSetActiveCamera : public Command {
public:
    using Method = void(RenderManager::*)(const Composite&, ObjectId id);

    inline CSetActiveCamera(ObjectId cameraId)
        : _method(&RenderManager::setActiveCamera)
        , _cameraId(cameraId) {
    }
    virtual void execute(Composite& scene, Manager& manager) override {
        (dynamic_cast<RenderManager&>(manager).*_method)(scene, _cameraId);
    }
    virtual const std::type_info& neededManager() const noexcept override {
        return typeid(RenderManager);
    }

private:
    Method _method;
    ObjectId _cameraId;
};

class CRender : public Command {
public:
    using Method = void(RenderManager::*)(const Composite&, std::weak_ptr<Painter>, ObjectId);

    inline CRender(const std::weak_ptr<Painter>& painter, ObjectId targetId)
        : _method(&RenderManager::render)
        , _painter(painter)
        , _targetId(targetId) {
    }

    virtual void execute(Composite& scene, Manager& manager) override {
        (dynamic_cast<RenderManager&>(manager).*_method)(scene, _painter, _targetId);
    }
    virtual const std::type_info& neededManager() const noexcept override {
        return typeid(RenderManager);
    }

private:
    Method _method;
    std::weak_ptr<Painter> _painter;
    ObjectId _targetId;
};

}