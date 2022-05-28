#pragma once
#include "jmanager.h"
#include "jcomposite.h"
#include "jpainter.h"
#include "jrenderer.h"
#include <unordered_map>

namespace Jora {

class RenderManager : public Manager {
public:
    inline void render(Painter& painter, const SceneObject& target) {
        if (target.isComposite()) {
            for (const auto& el : target)
                render(painter, *el);
        }
        else if (target.visible()) {
            _renderers[typeid(target)]->render(painter, *_currentCamera.lock(), target);
        }
    }

    inline void setActiveCamera(const std::weak_ptr<Camera3D>& camera) { _currentCamera = camera; }

    inline void addRenderer(const std::shared_ptr<Renderer>& renderer) {
        _renderers[typeid(*renderer)] = renderer;
    }
    inline void clear() { _renderers.clear(); }

private:
    std::unordered_map<std::type_index, std::shared_ptr<Renderer>> _renderers;
    std::weak_ptr<Camera3D> _currentCamera;
};

}
