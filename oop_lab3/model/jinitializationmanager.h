#pragma once
#include "jmanager.h"
#include "jmodelviewer.h"
#include "jmodel3d.h"
#include "jcamera.h"

namespace Jora {

class InitializationManager : public Manager {
public:
    std::unique_ptr<ModelViewer> createModelViewer();
    ObjectId createModel(Composite& group, const std::string& filename);
    ObjectId createCamera3D(Composite& group);
};

}