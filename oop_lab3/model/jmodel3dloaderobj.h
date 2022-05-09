#pragma once
#include "jmodel3dloader.h"
#include <list>

namespace Jora {

class Model3DLoaderObj : public Model3DLoader {
public:
    Model3DLoaderObj() = default;
    Model3DLoaderObj(const Model3DLoaderObj& other) = default;

protected:
    virtual std::unique_ptr<Model3D> loadModel(std::ifstream&& stream) override;
    virtual void applyInstruction(Model3D& model, std::istream&& stream, std::string&& instruction);
    virtual Point3D parsePoint(std::istream&& stream);
    virtual std::list<int> parseFace(std::istream&& stream);
    virtual std::list<Triangle3D> triangulate(std::list<int>&& indexes);

private:
    static constexpr const char* vertexWord = "v";
    static constexpr const char* faceWord = "f";
};

}
