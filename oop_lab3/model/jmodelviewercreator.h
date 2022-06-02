#pragma once
#include "jmodelviewer.h"

namespace Jora {

class ModelViewerCreator {
public:
    std::unique_ptr<ModelViewer> create();
};

}