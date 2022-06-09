#pragma once
#include "jmodel3d_impl.h"
#include <vector>
#include <list>

namespace Jora {

class PolygonalModel3DImpl : public Model3DImpl {
public:
    using Self = PolygonalModel3DImpl;
    using Face = std::array<size_t, 3>;
    using Vertex = Vector3D;
    using FaceIterator = std::list<Face>::iterator;
    using FaceConstIterator = std::list<Face>::const_iterator;

    virtual Vertex& vertex(size_t index);
    virtual const Vertex& vertex(size_t index) const;
    virtual size_t vertexCount() const noexcept;
    virtual Self& addVertex(Vertex&& vertex);

    virtual Self& addFace(Face&& face) noexcept;
    virtual size_t faceCount() const noexcept;
    virtual FaceIterator begin() noexcept;
    virtual FaceIterator end() noexcept;
    virtual FaceConstIterator cbegin() const noexcept;
    virtual FaceConstIterator cend() const noexcept;
    virtual FaceConstIterator begin() const noexcept;
    virtual FaceConstIterator end() const noexcept;

    void clear();

    virtual operator bool() const noexcept override;
    virtual bool isValid() const noexcept override;

private:
    std::vector<Vertex> _vertex;
    std::list<Face> _face;
};

}