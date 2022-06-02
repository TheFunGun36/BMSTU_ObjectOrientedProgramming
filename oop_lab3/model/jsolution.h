#pragma once
#include "jsceneobjectcreator.h"
#include "jmodelviewercreator.h"
#include "jwireframemodelcreator.h"
#include "jcameracreator.h"

namespace Jora {

class Solution {
public:
    inline virtual std::unique_ptr<ModelViewerCreator> modelViewerCreator() {
        return std::make_unique<ModelViewerCreator>();
    }
    inline virtual std::unique_ptr<Model3DDirector> modelCreator(const std::string& filename) {
        auto tmp =  std::make_unique<WireframeModel3DStreamDirector>();
        tmp->openStream(filename);
        return tmp;
    }
    inline virtual std::unique_ptr<CameraCreator> cameraCreator() {
        return std::make_unique<CameraCreator>();
    }
};

}