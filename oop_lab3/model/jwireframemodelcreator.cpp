#include "pch.h"
#include "jwireframemodelcreator.h"
#include "jwireframemodel3d_impl.h"
#include "jvector3d.h"
#include <istream>
#include <sstream>

namespace Jora {
using Builder = WireframeModel3DStreamBuilder;
using Director = WireframeModel3DStreamDirector;

Director::WireframeModel3DStreamDirector(std::istream& stream, const std::string& label)
    : _label(label)
    , _stream(stream) {
}

std::unique_ptr<SceneObject> Director::create() const {
    WireframeModel3DStreamBuilder builder;
    std::unique_ptr<SceneObject> result;
    if (builder.createModel(_label) &&
        builder.readData(_stream) &&
        builder.validate())
        result = builder.get();
    return result;
}

bool Builder::createModel(const std::string& label) noexcept {
    _model = std::make_unique<Model3D>(WireframeModel3DImpl(), label);
    return bool(_model);
}

bool Builder::readData(std::istream& stream) noexcept {
    std::string line;
    bool result = true;
    while (result && std::getline(stream, line))
        result = processLine(std::stringstream(line));
    return true;
}

bool Builder::validate() noexcept {
    return _model->isValid();
}

bool Builder::processLine(std::istream&& lineStream) {
    bool result = false;
    std::string firstWord;

    if (lineStream >> firstWord) {
        if (firstWord == "v")
            result = processPoint(std::move(lineStream));
        else if (firstWord == "f")
            result = processEdge(std::move(lineStream));
    }

    return result;
}

bool Builder::processPoint(std::istream&& lineStream) {
    Vector3D point;
    bool result = false;

    if (lineStream >> point.x() >> point.y() >> point.z()) {
        result = true;
        *_model << point;
    }

    return result;
}

bool Builder::processEdge(std::istream&& lineStream) {
    using std::make_pair;
    bool result = false;

    std::string junk;
    size_t first;
    if (lineStream >> first) {
        lineStream >> junk; // skip /1/2 "f 1/2/3 4/5/6 7/8/9" or "f 1 4 7"
        WireframeModel3DImpl& impl = dynamic_cast<WireframeModel3DImpl&>(*_model->implementation());

        size_t second;
        while (lineStream >> second) {
            lineStream >> junk;
            impl << make_pair(first, second);
            first = second;
        }
    }

    return result;
}



}