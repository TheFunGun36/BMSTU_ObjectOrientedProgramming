#pragma once
#include <qgraphicsview.h>
#include <qcolor.h>
#include <qlist.h>

class Canvas : public QGraphicsView {
    Q_OBJECT

public:
    Canvas(QWidget *parent = nullptr);

private:
    QGraphicsScene scene;
    int сellSize;
    QColor colorBackground;
    QColor colorAxes;
    QColor colorGrid;
    QColor colorGridAccent;
};

