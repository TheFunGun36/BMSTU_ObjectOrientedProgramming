#include "pch.h"
#include "jrenderer.h"
#include <cmath>

namespace Jora {

inline void WireframeModelRenderer::render(Painter& painter, const Camera3D& camera, const SceneObject& sceneObject) {
    const auto& model = dynamic_cast<const Model3D&>(sceneObject);
    const auto& impl = dynamic_cast<const WireframeModel3DImpl&>(model.implementation());

    for (int i = 0; i < impl.edgesAmount(); i++) {
        ScreenLine line;

        bool succeed = project(line.p1(), model[impl[i].first], camera);
        if (succeed && project(line.p2(), model[impl[i].second], camera))
            painter.drawLine(line);
    }
}

bool Renderer::project(ScreenPoint& dst, const Vector3D& src, const Camera3D& camera) {
    const Transform& ctr = camera.transform();
    const Vector3D& cpos = ctr.position();
    const EulerAngles& crot = ctr.rotation();

    // Translate input point using camera position
    real inputX = src.x() - cpos.x();
    real inputY = src.y() - cpos.y();
    real inputZ = src.z() - cpos.z();

    real aspectRatio = real(camera.viewWidth()) / camera.viewHeight();

    // Apply projection to X and Y
    dst.x() = int(round(inputX / -inputZ / tan(camera.fieldOfView() / 2.)));
    dst.y() = int(round(inputY * aspectRatio / -inputZ / tan(camera.fieldOfView() / 2.)));

    // Convert to screen coordinates
    dst.x() = int(round(dst.x() * camera.viewWidth()));
    dst.y() = int(round(dst.y() * camera.viewHeight()));

    return true;
}

}