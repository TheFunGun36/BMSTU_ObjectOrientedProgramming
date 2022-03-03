#include "Canvas.h"
#include <qpainter.h>

constexpr int maxDist = 4000;
constexpr int gridStep = 50;

Canvas::Canvas(QWidget *parent)
    : scene(this), QGraphicsView(parent) {
    colorX = {200, 0, 0};
    colorY = {0, 200, 0};
    colorZ = {0, 0, 200};
    colorLine = {0, 0, 0};
    colorPoly = {50, 50, 50, 10};
    setScene(&scene);
}

void Canvas::setModel(const wireframe::Model3D &model) {
    scene.clear();
    scene.update();

    for (auto face : model.face) {
        QPolygonF poly;
        for (auto i : face.vertexIdx) {
            QPointF p(model.vertex[i].x, -model.vertex[i].y);
            poly.append(p);
        }

        scene.addPolygon(poly, QPen(), colorPoly);
    }

    QRectF newScene;
    for (const auto &v : model.vertex) {
        newScene.setTop(qMin(-v.y, newScene.top()));
        newScene.setBottom(qMax(-v.y, newScene.bottom()));
        newScene.setLeft(qMin(v.x, newScene.left()));
        newScene.setRight(qMax(v.x, newScene.right()));
    }

    scene.setSceneRect(newScene.marginsAdded({ 75, 75, 75, 75 }));

    scene.addLine(0, 0, scene.sceneRect().right() - 25, 0, QPen(colorX, 2));
    scene.addLine(0, 0, 0, scene.sceneRect().top() + 25, QPen(colorY, 2));
    scene.addEllipse(-5, -5, 10, 10, colorZ, colorZ);
    QPolygonF arrowX({
        { scene.sceneRect().right() - 15, 0 },
        { scene.sceneRect().right() - 25, 5 },
        { scene.sceneRect().right() - 25, -5 }
        });
    QPolygonF arrowY({
        { 0, scene.sceneRect().top() + 15 },
        { 5, scene.sceneRect().top() + 25 },
        { -5, scene.sceneRect().top() + 25 }
        });
    scene.addPolygon(arrowX, colorX, colorX);
    scene.addPolygon(arrowY, colorY, colorY);
}
