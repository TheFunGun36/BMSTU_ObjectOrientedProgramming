#pragma once
#include "jsceneobjectcreator.h"
#include "jmodel3d.h"

namespace Jora {

class Model3DBuilder {
public:
    virtual bool createModel(const std::string& label) noexcept = 0;
    virtual bool readData(std::istream& stream) noexcept = 0;
    virtual bool validate() noexcept = 0;
    
    inline std::unique_ptr<Model3D> get() { return std::move(_model); };

protected:
    std::unique_ptr<Model3D> _model;
};

class Model3DDirector : public SceneObjectCreator {
};

}
