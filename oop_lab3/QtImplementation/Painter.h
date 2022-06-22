#pragma once
#include "qpainter.h"
#include "../model/jpainter.h"

class QtPainter : public Jora::Painter {
public:
    QtPainter(QPainter& qp);

    operator QPainter&() { return qp; }

    void drawLine(Jora::ScreenLine line) override;
    void drawRect(Jora::ScreenRect rect) override;
    void drawPoly(const std::list<Jora::ScreenPoint>& verticies) override;
    void drawPixel(Jora::ScreenPoint pixel) override;
    void drawEllipse(Jora::ScreenRect ellipse) override;
    void drawCircle(Jora::ScreenPoint center, int radius) override;

    void setOutlineColor(const Jora::Color& color) override;
    void setOutlineWidth(int value) override;

    void setFillColor(const Jora::Color& color) override;

private:
    QPainter& qp;
};

