#pragma once
#include <qgraphicsview.h>
#include <qcolor.h>
#include <qlist.h>
#include "Model3D.h"

class Canvas : public QGraphicsView {
    Q_OBJECT

public:
    Canvas(QWidget *parent = nullptr);
    bool setModel(const wireframe::Model3D &model, bool perspective);

private:
    QColor colorX;
    QColor colorY;
    QColor colorZ;
    QColor colorLine;
    QColor colorPoly;

    qreal cameraDistance;

    QGraphicsScene scene;
    int сellSize;

    bool toPerspective(QPointF &p, const wireframe::Vertex3D &v);
};

