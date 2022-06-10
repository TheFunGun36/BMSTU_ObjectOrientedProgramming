#include "pch.h"
#include "jpolygonalmodel3d_impl.h"

namespace Jora {

using std::move;

PolygonalModel3DImpl::Vertex& PolygonalModel3DImpl::vertex(size_t index) {
    return _vertex[index];
}

const PolygonalModel3DImpl::Vertex& PolygonalModel3DImpl::vertex(size_t index) const {
    return _vertex[index];
}

PolygonalModel3DImpl& PolygonalModel3DImpl::addVertex(PolygonalModel3DImpl::Vertex&& vertex) {
    _vertex.push_back(move(vertex));
    return *this;
}

size_t PolygonalModel3DImpl::vertexCount() const noexcept {
    return _vertex.size();
}

PolygonalModel3DImpl& PolygonalModel3DImpl::addFace(PolygonalModel3DImpl::Face&& face) noexcept {
    _face.push_back(move(face));
    return *this;
}

size_t PolygonalModel3DImpl::faceCount() const noexcept {
    return _face.size();
}

PolygonalModel3DImpl::operator bool() const noexcept {
    return isValid();
}

bool PolygonalModel3DImpl::isValid() const noexcept {
    bool result = vertexCount() || faceCount();
    for (auto it = begin(); result && it != end(); it++) {
        const Face &face = *it;
        for (int i = 0; result && i < face.size(); i++)
            result = face[i] < vertexCount();
    }
    return result;
}

PolygonalModel3DImpl::FaceIterator PolygonalModel3DImpl::begin() noexcept {
    return _face.begin();
}

PolygonalModel3DImpl::FaceIterator PolygonalModel3DImpl::end() noexcept {
    return _face.end();
}

PolygonalModel3DImpl::FaceConstIterator PolygonalModel3DImpl::cbegin() const noexcept {
    return _face.cbegin();
}

PolygonalModel3DImpl::FaceConstIterator PolygonalModel3DImpl::cend() const noexcept {
    return _face.cend();
}

PolygonalModel3DImpl::FaceConstIterator PolygonalModel3DImpl::begin() const noexcept {
    return _face.begin();
}

PolygonalModel3DImpl::FaceConstIterator PolygonalModel3DImpl::end() const noexcept {
    return _face.end();
}

void PolygonalModel3DImpl::clear() {
    _vertex.clear();
    _face.clear();
}

}
