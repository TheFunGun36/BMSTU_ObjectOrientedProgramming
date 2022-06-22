#include "pch.h"
#include "jinitializationmanager.h"
#include "jpolygonalmodelcreator.h"
#include "jcameracreator.h"
#include "jmodelviewercreator.h"
#include "jrendermanager.h"
#include "jscenemanager.h"
#include <fstream>

namespace Jora {

using std::shared_ptr, std::unique_ptr, std::make_shared, std::make_unique, std::move;

template<typename Derived, typename Base>
unique_ptr<Derived> staticUniquePtrCast(std::unique_ptr<Base>&& p) {
    auto d = static_cast<Derived*>(p.release());
    return unique_ptr<Derived>(d);
}

unique_ptr<ModelViewer> InitializationManager::createModelViewer() {
    unique_ptr<ModelViewer> result = make_unique<ModelViewer>();
    result->addManager(make_shared<InitializationManager>(*this));
    auto renderMgr = make_shared<RenderManager>();
    renderMgr->addRenderer(typeid(Model3D), make_shared<PolygonalModelRenderer>());
    result->addManager(renderMgr);
    result->addManager(make_shared<SceneManager>());
    return result;
}

unique_ptr<Model3D> InitializationManager::createModel(const std::string& filename) {
    unique_ptr<Model3D> result = nullptr;
    PolygonalModel3DStreamDirector creator;
    if (creator.openStream(filename))
        result = staticUniquePtrCast<Model3D, SceneObject>(creator.create());
    return result;
}

unique_ptr<Camera3D> InitializationManager::createCamera3D() {
    CameraCreator creator;
    return staticUniquePtrCast<Camera3D, SceneObject>(creator.create());
}

}
