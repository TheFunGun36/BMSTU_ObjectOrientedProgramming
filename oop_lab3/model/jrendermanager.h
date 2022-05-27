#pragma once
#include "jmanager.h"
#include "jcomposite.h"
#include <unordered_map>

namespace Jora {

class RenderManager {
public:
    void render(Painter& painter, const Composite& target);

private:
    std::unordered_map<const std::type_info&, Renderer> _renderers;
};

}
