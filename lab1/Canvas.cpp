#include "Canvas.h"
#include <qpainter.h>

constexpr int maxDist = 4000;
constexpr int gridStep = 50;

Canvas::Canvas(QWidget *parent)
    : scene(this), QGraphicsView(parent) {
    setScene(&scene);

    colorBackground = QColor(255, 255, 255);
    colorAxes = QColor(0, 100, 150);
    colorGrid = QColor(0, 200, 200);
    colorGridAccent = QColor(0, 50, 150);

    scene.setBackgroundBrush(colorBackground);
    scene.addEllipse(0, 0, 30, 30);
}


