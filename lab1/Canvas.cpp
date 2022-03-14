#include "Canvas.hpp"
#include <qpainter.h>
#include <qgraphicsitem.h>

Canvas::Canvas(QWidget *parent)
    : scene(this), QGraphicsView(parent) {
    colorX = {200, 0, 0};
    colorY = {0, 200, 0};
    colorZ = { 0, 0, 200 };
    colorC = { 100, 0, 200 };
    colorLine = {0, 0, 0};
    colorPoly = {50, 50, 50, 10};
    cameraDistance = 200;
    setScene(&scene);
}

void Canvas::updateProjection(const Projection &proj) {
    scene.clear();
    scene.update();

    for (int i = 0; i < proj.polygonAmount; i++) {
        QPolygonF poly;
        for (int j = 0; j < proj.polygonArray[i].verticiesAmount; j++) {
            size_t idx = proj.polygonArray[i].vertexIndexArray[j];
            poly.append(QPointF(proj.pointArray[idx].x, proj.pointArray[idx].y));
        }

        scene.addPolygon(poly, QPen(), colorPoly);
    }

    QRectF newScene;
    for (int i = 0; i < proj.pointsAmount; i++) {
        Point2D &v = proj.pointArray[i];
        newScene.setTop(qMin(v.y, newScene.top()));
        newScene.setBottom(qMax(v.y, newScene.bottom()));
        newScene.setLeft(qMin(v.x, newScene.left()));
        newScene.setRight(qMax(v.x, newScene.right()));
    }

    scene.setSceneRect(newScene.marginsAdded({ 75, 75, 75, 75 }));

    scene.addLine(0, 0, scene.sceneRect().right() - 25, 0, QPen(colorX, 2));
    QPolygonF arrowX({
        { scene.sceneRect().right() - 15, 0 },
        { scene.sceneRect().right() - 25, 5 },
        { scene.sceneRect().right() - 25, -5 }
        });
    scene.addPolygon(arrowX, colorX, colorX);
    auto text = scene.addText("X");
    text->setPos(scene.sceneRect().right() - 18, 0);
    text->setDefaultTextColor(colorX);

    scene.addLine(0, 0, 0, scene.sceneRect().top() + 25, QPen(colorY, 2));
    QPolygonF arrowY({
        { 0, scene.sceneRect().top() + 15 },
        { 5, scene.sceneRect().top() + 25 },
        { -5, scene.sceneRect().top() + 25 }
        });
    scene.addPolygon(arrowY, colorY, colorY);
    text = scene.addText("Y");
    text->setPos(3, scene.sceneRect().top() + 3);
    text->setDefaultTextColor(colorY);

    scene.addEllipse(-5, -5, 10, 10, colorZ, colorZ);
    text = scene.addText("Z");
    text->setPos(-16, -2);
    text->setDefaultTextColor(colorZ);

    const Point2D &c = proj.center;
    scene.addEllipse(c.x - 3, -c.y - 3, 6, 6, colorC, colorC);
    text = scene.addText("C");
    text->setPos(c.x, -c.y);
    text->setDefaultTextColor(colorC);

    scene.setSceneRect(-2000.0, -2000.0, 4000.0, 4000.0);
    centerOn(0, 0);
}

void Canvas::onResize() {
    centerOn(0, 0);
}
