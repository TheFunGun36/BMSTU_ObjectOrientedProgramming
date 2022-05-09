#include "pch.h"
#include <sstream>
#include "jmodel3dloaderobj.h"

namespace Jora {

std::unique_ptr<Model3D> Model3DLoaderObj::loadModel(std::ifstream&& stream) {
    std::unique_ptr<Model3D> model = std::make_unique<Model3D>();

    std::string line;
    int lineCount = 0;

    while (std::getline(stream, line)) {
        std::stringstream lineStream(line);
        std::string instruction;
        if (lineStream >> instruction) {
            try {
                applyInstruction(*model, std::move(lineStream), std::move(instruction));
            }
            catch (FileException& e) {
                e.setFileLine(lineCount);
                throw e;
            }
        }

        lineCount++;
    }

    return model;
}

void Model3DLoaderObj::applyInstruction(Model3D& model, std::istream&& stream, std::string&& instruction) {
    if (instruction == vertexWord) {
        model.addPoint(parsePoint(std::move(stream)));
    }
    else if (instruction == faceWord) {
        auto indexes = parseFace(std::move(stream));
        auto triangles = triangulate(std::move(indexes));
        for (Triangle3D& triangle : triangles)
            model.addTriangle(triangle);
    }
}

Point3D Model3DLoaderObj::parsePoint(std::istream&& stream) {
    Vector3D vertex;
    if (!(stream >> vertex.x() >> vertex.y() >> vertex.z()))
        throw FileInvalidVertex(__FILE__, __FUNCTION__, __LINE__);
    return Point3D(vertex);
}

std::list<int> Model3DLoaderObj::parseFace(std::istream&& stream) {
    std::list<int> result;

    int value;
    std::string skippedWord;
    while (stream >> value) {
        result.push_back(value);
        stream >> skippedWord;
    }

    return result;
}

std::list<Triangle3D> Model3DLoaderObj::triangulate(std::list<int>&& indexes) {
    if (indexes.size() < 3)
        throw FileInvalidFace(__FILE__, __FUNCTION__, __LINE__);

    std::list<Triangle3D> result;

    //wow
    auto it3 = result.begin();
    auto it2 = it3++;
    auto it1 = it2++;

    do {
        Triangle3D triangle;
        triangle.setIndexes(*it1, *it2, *it3);
        result.push_back(triangle);
        ++it1; ++it2; ++it3;
        result.pop_front();
    }
    while (indexes.size() >= 3);

    return result;
}

}
