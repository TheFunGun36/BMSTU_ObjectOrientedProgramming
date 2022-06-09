#pragma once
#include "jsceneobjectcreator.h"
#include "jmodel3d.h"

namespace Jora {

class Model3DBuilder {
public:
    virtual bool createModel() noexcept = 0;
    virtual bool readData(std::istream& stream) noexcept = 0;
    virtual bool validate() noexcept = 0;
    
    inline std::unique_ptr<Model3D> get() { return std::move(_model); };

protected:
    std::unique_ptr<Model3D> _model;
};

class Model3DDirector : public SceneObjectCreator {
public:
    virtual void assignStream(const std::shared_ptr<std::istream>& stream) noexcept = 0;
    virtual bool openStream(const std::string& filename) = 0;
};

}
