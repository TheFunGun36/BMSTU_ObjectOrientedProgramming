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
    Jora::ObjectId currentObject();

    double fov = 90.;

private slots:
    void onTransform(double);

    void onAddCamera();
    void onAddModel();
    void onRemove();
    void onClear();
    void onUpdateSelection(const QModelIndex& index);
    void upd(QPainter &qp);
};
