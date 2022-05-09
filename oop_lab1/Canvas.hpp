#pragma once
#include <qgraphicsview.h>
#include <qcolor.h>
#include <qlist.h>
#include <cstring>
#include "Projection.hpp"

class Canvas : public QGraphicsView {
    Q_OBJECT

public:
    Canvas(QWidget *parent = nullptr);
    void updateProjection(const Projection &projection);

public slots:
    void onResize();

private:
    QColor colorX;
    QColor colorY;
    QColor colorZ;
    QColor colorC;
    QColor colorLine;
    QColor colorPoly;

    qreal cameraDistance;

    QGraphicsScene scene;
    int cellSize;
};

