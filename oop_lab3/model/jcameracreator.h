#pragma once
#include "jsceneobjectcreator.h"
#include "jcamera.h"

namespace Jora {

class CameraCreator : public SceneObjectCreator {
public:
    inline virtual std::unique_ptr<SceneObject> create() const override {
        return std::make_unique<Camera3D>();
    }
};

}
