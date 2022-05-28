#pragma once
#include "jmanager.h"
#include "jmodelviewer.h"
#include "jmodel3d.h"
#include "jcamera.h"
#include "jsolution.h"

namespace Jora {

class InitializationManager : public Manager {
public:
    InitializationManager(std::shared_ptr<Solution> solution)
        : _solution(std::move(solution)) {
    }

    std::unique_ptr<ModelViewer> createModelViewer();
    std::unique_ptr<Model3D> createModel(const std::string& filename, const std::string& label);
    std::unique_ptr<Camera3D> createCamera3D(const std::string& label);

private:
    std::shared_ptr<Solution> _solution;
};

}