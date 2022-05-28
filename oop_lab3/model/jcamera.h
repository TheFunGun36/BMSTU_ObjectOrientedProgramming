#pragma once
#include "jsceneobject.h"

namespace Jora {

class Camera3D : public SceneObject {
public:
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
    size_t _viewWidth;
    size_t _viewHeight;
    real _fieldOfView = 90.;
};

}
