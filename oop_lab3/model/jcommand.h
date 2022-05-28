#pragma once
#include "jcomposite.h"
#include "jmanager.h"

namespace Jora {
class ModelViewer;

class Command {
public:
    virtual void execute(Composite& scene, Composite& selection, Manager& manager) = 0;
    virtual const std::type_info& neededManager() const noexcept = 0;
};
}
