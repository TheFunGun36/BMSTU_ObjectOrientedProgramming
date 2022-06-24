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

ObjectId InitializationManager::createModel(Composite& group, const std::string& filename) {
    shared_ptr<Model3D> result = nullptr;
    PolygonalModel3DStreamDirector creator;
    if (creator.openStream(filename)) {
        result = std::static_pointer_cast<Model3D, SceneObject>(creator.create());
        group.insert(result);
    }
    return result ? result->id() : 0;
}

ObjectId InitializationManager::createCamera3D(Composite& group) {
    CameraCreator creator;
    auto result = std::static_pointer_cast<Camera3D, SceneObject>(creator.create());
    if (result)
        group.insert(result);
    return result ? result->id() : 0;
}

}
