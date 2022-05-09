#pragma once
#include "Canvas.hpp"
#include <qmainwindow.h>
#include <qlayout.h>
#include <qspinbox.h>
#include <qevent.h>
#include "Model3D.hpp"
#include "ExecuteCmd.hpp"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QString currentFilename;
    bool perspective;
    Canvas *canvas;
    qreal cameraDistance;

    QDoubleSpinBox *spinMoveX;
    QDoubleSpinBox *spinMoveY;
    QDoubleSpinBox *spinMoveZ;

    QDoubleSpinBox *spinScaleX;
    QDoubleSpinBox *spinScaleY;
    QDoubleSpinBox *spinScaleZ;

    QDoubleSpinBox *spinRotateAngleX;
    QDoubleSpinBox *spinRotateAngleY;
    QDoubleSpinBox *spinRotateAngleZ;

    QAction *actionFileOpen;
    QAction *actionModelPerspective;

    void createMoveSection(QVBoxLayout *layout);
    void createScaleSection(QVBoxLayout *layout);
    void createRotateSection(QVBoxLayout *layout);
    void createMenu();
    void showError(Exit exitCode);
    void updateModel();

    virtual void resizeEvent(QResizeEvent *e) override;

private slots:
    void fileOpen();
    void moveModel();
    void scaleModel();
    void rotateModel();
    void togglePerspective();
    void undo();
};
