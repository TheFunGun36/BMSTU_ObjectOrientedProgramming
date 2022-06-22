#include "Painter.h"

QtPainter::QtPainter(QPainter& qp)
    : qp(qp) {}

void QtPainter::drawLine(Jora::ScreenLine line) {
    qp.drawLine(line.x1(), line.y1(), line.x2(), line.y2());
}

void QtPainter::drawRect(Jora::ScreenRect rect) {

}

void QtPainter::drawPoly(const std::list<Jora::ScreenPoint>& verticies) {}

void QtPainter::drawPixel(Jora::ScreenPoint pixel) {}

void QtPainter::drawEllipse(Jora::ScreenRect ellipse) {}

void QtPainter::drawCircle(Jora::ScreenPoint center, int radius) {}

void QtPainter::setOutlineColor(const Jora::Color& color) {
    auto pen = qp.pen();
    pen.setColor(QColor(color.r(), color.g(), color.b(), color.a()));
    qp.setPen(pen);
}

void QtPainter::setOutlineWidth(int value) {
    auto pen = qp.pen();
    pen.setWidth(value);
    qp.setPen(pen);
}

void QtPainter::setFillColor(const Jora::Color& color) {
    auto brush = qp.brush();
    brush.setColor(QColor(color.r(), color.g(), color.b(), color.a()));
    qp.setBrush(brush);
}
