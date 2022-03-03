#pragma once
#include <qgraphicsview.h>
#include <qcolor.h>
#include <qlist.h>
#include "Model3D.h"

class Canvas : public QGraphicsView {
    Q_OBJECT

public:
    Canvas(QWidget *parent = nullptr);
    void setModel(const wireframe::Model3D &model);

private:
    QColor colorX;
    QColor colorY;
    QColor colorZ;
    QColor colorLine;
    QColor colorPoly;

    QGraphicsScene scene;
    int сellSize;
};

