#include "Canvas.h"
#include "qpainter.h"

Canvas::Canvas(QWidget* parent)
    : QWidget(parent) {
}

void Canvas::paintEvent(QPaintEvent* e) {
    QPainter qp(this);
    qp.fillRect(-1, -1, width() + 2, height() + 2, Qt::white);
    emit paint(qp);
}
