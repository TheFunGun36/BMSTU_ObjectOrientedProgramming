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
    inline WireframeModel3DStreamDirector() = default;

    virtual std::unique_ptr<SceneObject> create(const std::string& label) const override;

    void assignStream(const std::shared_ptr<std::istream>& stream) noexcept override;
    bool openStream(const std::string& filename) override;

private:
    std::shared_ptr<std::istream> _stream;
};

}