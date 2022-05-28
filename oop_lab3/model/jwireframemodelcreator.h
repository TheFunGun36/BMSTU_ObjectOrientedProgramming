#pragma once
#include "jmodelcreator.h"

namespace Jora {

class WireframeModel3DStreamBuilder : public Model3DBuilder {
public:
    virtual bool createModel(const std::string& label) noexcept override;
    virtual bool readData(std::istream& stream) noexcept override;
    virtual bool validate() noexcept override;

private:
    bool processLine(std::istream&& lineStream);
    bool processPoint(std::istream&& lineStream);
    bool processEdge(std::istream&& lineStream);
};

class WireframeModel3DStreamDirector : public Model3DDirector {
public:
    WireframeModel3DStreamDirector(std::istream& stream, const std::string& label);
    virtual std::unique_ptr<SceneObject> create() const;

private:
    std::string _label;
    std::istream& _stream;
};

}