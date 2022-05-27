#include "pch.h"
#include "jmodelviewercreator.h"
#include "jscenemanager.h"

namespace Jora {

std::unique_ptr<ModelViewer> ModelViewerCreator::create() {
    using namespace std;
    auto result = make_unique<ModelViewer>();
    result->addManager(SceneManager());
    return result;
}

}
