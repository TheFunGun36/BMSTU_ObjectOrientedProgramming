#include "pch.h"
#include "jmodel3dloader.h"

namespace Jora {

std::unique_ptr<Model3D> Model3DLoader::load(std::string filename, bool shouldThrow) {
    std::unique_ptr<Model3D> result = nullptr;
    try {
        result = loadModel(fileOpen(filename));
    }
    catch (FileException& e) {
        if (shouldThrow) {
            e.setFileName(std::move(filename));
            throw e;
        }
    }
    return result;
}

std::ifstream Model3DLoader::fileOpen(std::string filename) {
    std::ifstream stream(filename);
    if (!stream.is_open())
        throw FileNotOpen(__FILE__, __FUNCTION__, __LINE__);
    return stream;
}

}
