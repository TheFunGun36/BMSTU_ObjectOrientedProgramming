#pragma once
#include "jmodelcreator.h"

namespace Jora {

class PolygonalModel3DStreamBuilder : public Model3DBuilder {
public:
    virtual bool createModel() noexcept override;
    virtual bool readData(std::istream& stream) noexcept override;
    virtual bool validate() noexcept override;

private:
    bool processLine(std::istream&& lineStream);
    bool processVertex(std::istream&& lineStream);
    bool processFace(std::istream&& lineStream);
};

class PolygonalModel3DStreamDirector : public Model3DDirector {
public:
    inline PolygonalModel3DStreamDirector() = default;

    virtual std::unique_ptr<SceneObject> create() const override;

    void assignStream(const std::shared_ptr<std::istream>& stream) noexcept override;
    bool openStream(const std::string& filename) override;

private:
    std::shared_ptr<std::istream> _stream;
};

}