#include "pch.h"
#include "jrenderer.h"
#include <cmath>

namespace Jora {

inline void PolygonalModelRenderer::render(Painter& painter, const Camera3D& camera, const SceneObject& sceneObject) {
    auto implPtr = dynamic_cast<const Model3D&>(sceneObject).implementation();
    const auto& impl = dynamic_cast<const PolygonalModel3DImpl&>(*implPtr);

    for (auto face : impl) {
        ScreenPoint p[3];
        bool succeed[3];
        for (int i = 0; i < 3; i++)
            succeed[i] = project(p[i], impl.vertex(face[i]), camera);

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