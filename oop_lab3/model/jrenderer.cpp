#include "pch.h"
#include "jrenderer.h"
#include <cmath>

namespace Jora {

void PolygonalModelRenderer::render(Painter& painter, const Camera3D& camera, const SceneObject& sceneObject) {
    auto implPtr = dynamic_cast<const Model3D&>(sceneObject).implementation();
    const auto& impl = dynamic_cast<const PolygonalModel3DImpl&>(*implPtr);

    for (auto face : impl) {
        ScreenPoint p[3];
        bool succeed[3];
        for (int i = 0; i < 3; i++)
            succeed[i] = project(p[i], sceneObject.transform().pointLocalToGlobal(impl.vertex(face[i])), camera);

        for (int i = 0; i <= 1; i++) {
            for (int j = i + 1; j < 3; j++) {
                if (succeed[i] && succeed[j])
                    painter.drawLine(ScreenLine(p[i], p[j]));
            }
        }
    }
}

bool Renderer::project(ScreenPoint& dst, const Vector3D& src, const Camera3D& camera) {
    const Transform& ctr = camera.transform();
    const Vector3D& cpos = ctr.position();
    const EulerAngles& crot = ctr.rotation();


    // Translate input point using camera position
    Vector3D pt = camera.transform().pointGlobalToLocal(src);

    double cameraDistance = camera.projectionDistance();
    if (-pt.z() + cameraDistance > 0)
        return false;

    double k = cameraDistance / (-pt.z() + cameraDistance);
    dst = ScreenPoint(k * pt.x() + camera.viewWidth() / 2, k * pt.y() + camera.viewHeight() / 2);

    return true;
}

}