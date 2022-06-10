#pragma once
#include "jpainter.h"
#include "jcamera.h"
#include "jmodel3d.h"
#include "jpolygonalmodel3d_impl.h"

namespace Jora {

class Renderer {
public:
    virtual ~Renderer() = default;
    virtual void render(Painter& painter, const Camera3D& camera, const SceneObject& sceneObject) = 0;
protected:
    bool project(ScreenPoint &dst, const Vector3D& src, const Camera3D& camera);
};

class PolygonalModelRenderer : public Renderer {
public:
    virtual inline void render(Painter& painter, const Camera3D& camera, const SceneObject& sceneObject) override;
};

}
