#pragma once
#include "jsceneobject.h"

namespace Jora {

class Camera3D : public SceneObject {
public:
    inline Camera3D(const std::string& label)
        : SceneObject(label) {
    }
    inline size_t& viewWidth() { return _viewWidth; }
    inline size_t& viewHeight() { return _viewHeight; }
    inline real& fieldOfView() { return _fieldOfView; }

    inline size_t viewWidth() const { return _viewWidth; }
    inline size_t viewHeight() const { return _viewHeight; }
    inline const real& fieldOfView() const { return _fieldOfView; }

    inline void setViewWidth(size_t value) { _viewWidth = value; }
    inline void setViewHeight(size_t value) { _viewHeight = value; }
    inline void fieldOfView(real value) { _fieldOfView = value; }

protected:
    virtual std::ostream& addToStream(std::ostream& stream) const override {
        return stream << "Camera("
            << transform() << ", "
            << _viewWidth << 'x'
            << _viewHeight << ", fov:"
            << _fieldOfView << ")";
    };
    virtual std::wostream& addToStream(std::wostream& stream) const override {
        return stream << L"Camera("
            << transform() << L", "
            << _viewWidth << L'x'
            << _viewHeight << L", fov:"
            << _fieldOfView << L")";
    };
    size_t _viewWidth = 0;
    size_t _viewHeight = 0;
    real _fieldOfView = 90.;
};

}
