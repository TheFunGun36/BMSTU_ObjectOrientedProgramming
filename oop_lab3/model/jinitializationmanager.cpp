#include "pch.h"
#include "jinitializationmanager.h"
#include "jwireframemodelcreator.h"
#include "jmodelviewercreator.h"

namespace Jora {

template <typename To, typename From>
std::unique_ptr<To> dyncast(std::unique_ptr<From> ptr) {
    std::unique_ptr<To> result;
    result.reset(dynamic_cast<To*>(ptr.get()));
    ptr.release();
    return result;
}

std::unique_ptr<ModelViewer> InitializationManager::createModelViewer() {
    return _solution->modelViewerCreator()->create();
}

std::unique_ptr<Model3D> InitializationManager::createModel(const std::string& filename, const std::string& label) {
    return dyncast<Model3D, SceneObject>(_solution->modelCreator(filename)->create(label));
}

std::unique_ptr<Camera3D> InitializationManager::createCamera3D(const std::string& label) {
    return dyncast<Camera3D, SceneObject>(_solution->cameraCreator()->create(label));
}

}
