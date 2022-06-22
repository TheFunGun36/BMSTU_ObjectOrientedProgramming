#include "pch.h"
#include "jmodelviewer.h"

namespace Jora {

ModelViewer::ModelViewer()
    : _scene("Scene")
    , _selection("Selection") {
}

void ModelViewer::execute(Command&& cmd) {
    cmd.execute(_scene, *_managers[cmd.neededManager()]);
}

void ModelViewer::addManager(const std::shared_ptr<Manager>& manager) {
    _managers[typeid(*manager)] = manager;
}

void ModelViewer::clear() {
    _managers.clear();
}

}
