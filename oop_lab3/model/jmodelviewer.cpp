#include "pch.h"
#include "jmodelviewer.h"

namespace Jora {

void ModelViewer::execute(Command&& cmd) {
    cmd.execute(_scene, _selection, *_managers[cmd.neededManager()]);
}

void ModelViewer::addManager(const std::shared_ptr<Manager>& manager) {
    _managers[typeid(manager)] = manager;
}

void ModelViewer::clear() {
    _managers.clear();
}

}
