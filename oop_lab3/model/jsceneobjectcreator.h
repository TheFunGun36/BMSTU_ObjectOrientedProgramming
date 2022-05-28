#pragma once
#include "jsceneobject.h"

namespace Jora {

class SceneObjectCreator {
public:
    virtual std::unique_ptr<SceneObject> create() const = 0;
};

}
