#include "pch.h"
#include "jmodelviewercreator.h"
#include "jscenemanager.h"

namespace Jora {

std::unique_ptr<ModelViewer> ModelViewerCreator::create() {
    using std::make_unique, std::make_shared;
    auto result = make_unique<ModelViewer>();

    result->addManager(make_shared<SceneManager>());

    return result;
}

}
