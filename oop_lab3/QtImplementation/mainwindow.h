#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"
#include "../model/jsceneobject.h"
#include "../model/jmodelviewer.h"
#include "../model/jscenemanagercommands.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = Q_NULLPTR);

private:
    Ui::MainWindowClass ui;
    std::unique_ptr<Jora::ModelViewer> modelViewer;
    Jora::ObjectId currentObject;

private slots:
    void onMove();
    void onScale();
    void onRotate();
    void onAddCamera();
    void onAddModel();
    void onRemove();
    void onClear();
};
