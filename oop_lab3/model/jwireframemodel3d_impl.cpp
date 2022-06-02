#include "pch.h"
#include "jwireframemodel3d_impl.h"

namespace Jora {
using Edge = WireframeModel3DImpl::Edge;

Edge& WireframeModel3DImpl::edge(size_t index) {
    return _edges[index];
}
Edge& WireframeModel3DImpl::operator[](size_t index) {
    return _edges[index];
}
const Edge& WireframeModel3DImpl::edge(size_t index) const {
    return _edges[index];
}
const Edge& WireframeModel3DImpl::operator[](size_t index) const {
    return _edges[index];
}

WireframeModel3DImpl& WireframeModel3DImpl::addEdge(const Edge& edge) noexcept {
    _edges.push_back(edge);
    return *this;
}
WireframeModel3DImpl& WireframeModel3DImpl::operator<<(const Edge& edge) noexcept {
    _edges.push_back(edge);
    return *this;
}

size_t WireframeModel3DImpl::edgesAmount() const noexcept {
    return _edges.size();
}
WireframeModel3DImpl::operator bool() const noexcept {
    return !_edges.empty();
}

bool WireframeModel3DImpl::isEmpty() const noexcept {
    return _edges.empty();
}

bool WireframeModel3DImpl::isValid(size_t points_amount) {
    for (Edge e : _edges)
        if (e.first > points_amount || e.second > points_amount)
            return false;
    return true;
}

}
