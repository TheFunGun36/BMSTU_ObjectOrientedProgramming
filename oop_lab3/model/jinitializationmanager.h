#pragma once
#include "jmanager.h"
#include "jmodelviewer.h"
#include "jmodel3d.h"
#include "jcamera.h"

namespace Jora {

class InitializationManager : public Manager {
public:
    std::unique_ptr<ModelViewer> createModelViewer();
    std::unique_ptr<Model3D> createModel(const std::string& filename);
    std::unique_ptr<Camera3D> createCamera3D();
};

}