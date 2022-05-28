#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"
#include "../model/jmodelviewer.h"
#include "../model/jscenemanagercommands.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = Q_NULLPTR);

private:
    Ui::MainWindowClass ui;
    Jora::ModelViewer modelViewer;
};
