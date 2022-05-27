#include "pch.h"
#include "jmodelviewer.h"

namespace Jora {

void ModelViewer::execute(Command&& cmd) {
    cmd.execute(_scene, *this);
}

Manager& ModelViewer::manager(const std::type_info& managerType) {
    return _managers[managerType];
}

}
