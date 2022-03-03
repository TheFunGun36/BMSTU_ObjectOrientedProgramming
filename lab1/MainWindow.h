#pragma once
#include "canvas.h"
#include <qmainwindow.h>
#include <qlayout.h>
#include <qspinbox.h>
#include "Model3D.h"
#include "ProcessEntry.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Canvas *canvas;
    Model3D currentModel;
    wireframe::UserData *userData;

    QDoubleSpinBox *spinMoveDx;
    QDoubleSpinBox *spinMoveDy;
    QDoubleSpinBox *spinMoveDz;

    QDoubleSpinBox *spinScaleKx;
    QDoubleSpinBox *spinScaleKy;
    QDoubleSpinBox *spinScaleKz;
    QDoubleSpinBox *spinScaleCenterX;
    QDoubleSpinBox *spinScaleCenterY;
    QDoubleSpinBox *spinScaleCenterZ;

    QDoubleSpinBox *spinRotateAngleX;
    QDoubleSpinBox *spinRotateAngleY;
    QDoubleSpinBox *spinRotateAngleZ;
    QDoubleSpinBox *spinRotateCenterX;
    QDoubleSpinBox *spinRotateCenterY;
    QDoubleSpinBox *spinRotateCenterZ;

    void createMoveSection(QVBoxLayout *layout);
    void createScaleSection(QVBoxLayout *layout);
    void createRotateSection(QVBoxLayout *layout);
    void createMenu();

private slots:
    void fileOpen();
    void fileSave();
    void fileSaveAs();
};
