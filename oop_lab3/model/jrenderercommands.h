#pragma once
#include "jcommand.h"
#include "jrendermanager.h"
#include "jcamera.h"

namespace Jora {

class CSetActiveCamera : public Command {
public:
    using Method = void(RenderManager::*)(Composite&, ObjectId id);

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
    using Method = void(RenderManager::*)(const Composite&, std::weak_ptr<Painter>);

    inline CRender(const std::weak_ptr<Painter>& painter)
        : _method(&RenderManager::render)
        , _painter(painter) {
    }

    virtual void execute(Composite& scene, Manager& manager) override {
        (dynamic_cast<RenderManager&>(manager).*_method)(scene, _painter);
    }
    virtual const std::type_info& neededManager() const noexcept override {
        return typeid(RenderManager);
    }

private:
    Method _method;
    std::weak_ptr<Painter> _painter;
};

class CUpdateCamera : public Command {
public:
    using Method = void(RenderManager::*)(size_t, size_t, real);

    inline CUpdateCamera(size_t width, size_t height, real fov)
        : _method(&RenderManager::updateCameraSettings)
        , _width(width)
        , _height(height)
        , _fov(fov) {
    }

    virtual void execute(Composite& scene, Manager& manager) override {
        (dynamic_cast<RenderManager&>(manager).*_method)(_width, _height, _fov);
    }
    virtual const std::type_info& neededManager() const noexcept override {
        return typeid(RenderManager);
    }

private:
    Method _method;
    size_t _width;
    size_t _height;
    real _fov;
};

}