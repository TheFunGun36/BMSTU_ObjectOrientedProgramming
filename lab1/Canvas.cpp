#include "Canvas.h"
#include <qpainter.h>
#include <qgraphicsitem.h>

Canvas::Canvas(QWidget *parent)
    : scene(this), QGraphicsView(parent) {
    colorX = {200, 0, 0};
    colorY = {0, 200, 0};
    colorZ = {0, 0, 200};
    colorLine = {0, 0, 0};
    colorPoly = {50, 50, 50, 10};
    cameraDistance = 200;
    setScene(&scene);
}

bool Canvas::setModel(const wireframe::Model3D &model, bool perspective) {
    scene.clear();
    scene.update();

    for (const auto &face : model.face) {
        QPolygonF poly;
        for (auto i : face.vertexIdx) {
            QPointF p;
            if (!perspective) {
                p = QPointF(model.vertex[i].x, -model.vertex[i].y);
            }
            else if (!toPerspective(p, model.vertex[i])) {
                return false;
            }
            
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
    return true;
}


bool Canvas::toPerspective(QPointF &p, const wireframe::Vertex3D &v) {
    bool result = true;
    if (-v.z > cameraDistance) {
        result = false;
    }
    else {
        qreal k = cameraDistance / (v.z + cameraDistance);
        p.setX(v.x * k);
        p.setY(-v.y * k);
    }

    return result;
}