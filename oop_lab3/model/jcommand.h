#pragma once
#include "jcomposite.h"

namespace Jora {
class ModelViewer;

class Command {
public:
    virtual void execute(Composite& scene, ModelViewer& modelViewer) = 0;
};
}
