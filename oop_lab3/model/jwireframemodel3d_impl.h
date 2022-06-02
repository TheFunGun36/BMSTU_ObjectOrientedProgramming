#pragma once
#include "jmodel3d_impl.h"
#include <vector>

namespace Jora {

class WireframeModel3DImpl : public Model3DImpl {
public:
    using Self = WireframeModel3DImpl;
    using Edge = std::pair<size_t, size_t>;

    virtual Edge& edge(size_t index);
    virtual Edge& operator[](size_t index);
    virtual const Edge& edge(size_t index) const;
    virtual const Edge& operator[](size_t index) const;

    virtual Self& addEdge(const Edge& edge) noexcept;
    virtual Self& operator<<(const Edge& edge) noexcept;

    virtual size_t edgesAmount() const noexcept;

    virtual operator bool() const noexcept override;
    virtual bool isEmpty() const noexcept override;
    virtual bool isValid(size_t points_amount) override;

private:
    std::vector<Edge> _edges;
};

}