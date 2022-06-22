#pragma once
#include "jmanager.h"
#include "jcomposite.h"
#include "jpainter.h"
#include "jrenderer.h"
#include <unordered_map>

namespace Jora {

class RenderManager : public Manager {
public:
    inline void render(const Composite& scene, std::weak_ptr<Painter> painter, ObjectId id) {
        if (painter.expired() || _currentCamera.expired())
            return;

        std::shared_ptr<const SceneObject> targetLocked = scene[id];
        std::shared_ptr<Painter> painterLocked = painter.lock();

        const SceneObject& targetRef = *targetLocked;
        Painter& painterRef = *painterLocked;

        renderTarget(painterRef, targetRef);
    }

    inline void setActiveCamera(const Composite& scene, ObjectId id) {
        if (scene[id] && typeid(*scene[id]) == typeid(Camera3D))
            _currentCamera = std::static_pointer_cast<const Camera3D>(scene[id]);
    }

    inline void addRenderer(const std::shared_ptr<Renderer>& renderer) {
        _renderers[typeid(*renderer)] = renderer;
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
    std::weak_ptr<const Camera3D> _currentCamera;
};

}
