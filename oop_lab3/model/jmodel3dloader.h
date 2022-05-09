#pragma once
#include "jmodel3d.h"
#include "jfileexception.h"
#include <fstream>

namespace Jora {

class Model3DLoader {
public:
    virtual ~Model3DLoader() = default;

    virtual std::unique_ptr<Model3D> load(std::string filename, bool shouldThrow = true);

protected:
    Model3DLoader() = default;
    Model3DLoader(const Model3DLoader& other) = default;

    static std::ifstream fileOpen(std::string filename);
    virtual std::unique_ptr<Model3D> loadModel(std::ifstream &&stream) = 0;
};

}