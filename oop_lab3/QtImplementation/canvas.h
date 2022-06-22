#pragma once
#include <qwidget.h>

class Canvas : public QWidget {
    Q_OBJECT

public:
    Canvas(QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* e) override;

private:

signals:
    void paint(QPainter &painter);
};

