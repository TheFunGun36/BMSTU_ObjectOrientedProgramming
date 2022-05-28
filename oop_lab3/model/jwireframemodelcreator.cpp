#include "pch.h"
#include "jwireframemodelcreator.h"
#include "jwireframemodel3d_impl.h"
#include "jvector3d.h"
#include <istream>
#include <sstream>
#include <fstream>

namespace Jora {
using Builder = WireframeModel3DStreamBuilder;
using Director = WireframeModel3DStreamDirector;

std::unique_ptr<SceneObject> Director::create(const std::string& label) const {
    WireframeModel3DStreamBuilder builder;
    std::unique_ptr<SceneObject> result;
    if (builder.createModel(label) &&
        builder.readData(*_stream) &&
        builder.validate())
        result = builder.get();
    return result;
}



bool Builder::createModel(const std::string& label) noexcept {
    _model = std::make_unique<Model3D>(std::make_shared<WireframeModel3DImpl>(), label);
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

void Director::assignStream(const std::shared_ptr<std::istream>& stream) noexcept {
    _stream = stream;
}

bool Director::openStream(const std::string& filename) {
    auto tmp = std::make_shared<std::ifstream>(filename);
    bool result = false;

    if (tmp->is_open()) {
        _stream = tmp;
        result = true;
    }

    return result;
}


}