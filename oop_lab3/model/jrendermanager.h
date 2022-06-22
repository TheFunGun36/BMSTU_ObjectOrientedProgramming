#pragma once
#include "jmanager.h"
#include "jcomposite.h"
#include "jpainter.h"
#include "jrenderer.h"
#include <unordered_map>

namespace Jora {

class RenderManager : public Manager {
public:
    inline void render(const Composite& scene, std::weak_ptr<Painter> painter) {
        if (painter.expired() || _currentCamera.expired())
            return;

        std::shared_ptr<Painter> painterLocked = painter.lock();
        Painter& painterRef = *painterLocked;
        renderTarget(painterRef, scene);
    }

    inline void setActiveCamera(Composite& scene, ObjectId id) {
        if (scene[id] && typeid(*scene[id]) == typeid(Camera3D))
            _currentCamera = std::static_pointer_cast<Camera3D>(scene[id]);
    }

    inline void updateCameraSettings(size_t width, size_t height, real fov) {
        if (!_currentCamera.expired()) {
            auto camera = _currentCamera.lock();
            camera->setViewWidth(width);
            camera->setViewHeight(height);
            camera->setProjectionDistance(fov);
        }
    }

    inline void addRenderer(const std::type_info& visibleObject, const std::shared_ptr<Renderer>& renderer) {
        _renderers[visibleObject] = renderer;
    }
    inline void clear() { _renderers.clear(); }

private:
    inline void renderTarget(Painter& painter, const SceneObject& target) {
        if (target.isComposite()) {
            for (const auto& el : target)
                renderTarget(painter, *el.second);
        }
        else if (target.visible()) {
            _renderers[typeid(target)]->render(painter, *_currentCamera.lock(), target);
        }
    }

    std::unordered_map<std::type_index, std::shared_ptr<Renderer>> _renderers;
    std::weak_ptr<Camera3D> _currentCamera;
};

}
