#pragma once

#include <QtWidgets/QMainWindow>
#include <qvector.h>
#include "ui_MainWindow.h"
#include "Cabin.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = Q_NULLPTR);

private:
    Ui::MainWindowClass ui;
    Cabin _cabin;
    Button* _buttons[8];

    void buttonPressed(int index);
    void addToHistory(QString string);

private slots:
    void update();
};
