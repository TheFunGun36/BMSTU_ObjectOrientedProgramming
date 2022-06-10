#include "mainwindow.h"
#include "../model/jinitializationmanager.h"
#include "../model/jtransformaction.h"
#include "../model/jscenemanagercommands.h"
#include <qfiledialog.h>

using namespace Jora;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent) {
    ui.setupUi(this);

    InitializationManager im;
    modelViewer = im.createModelViewer();
}

void MainWindow::onMove() {
    Vector3D shift;
    shift.setX(ui.spinX->value());
    shift.setY(ui.spinY->value());
    shift.setZ(ui.spinZ->value());
    //auto command = CTransform(TransformMove(shift));
    //modelViewer->execute(command);
}

void MainWindow::onScale() {
    Vector3D scale;
    scale.setX(ui.spinX->value());
    scale.setY(ui.spinY->value());
    scale.setZ(ui.spinZ->value());
    //auto command = CTransform(TransformScale(scale));
    //modelViewer->execute(command);
}

void MainWindow::onRotate() {
    EulerAngles angles;
    angles.setX(Angle::fromDegrees(ui.spinX->value()));
    angles.setY(Angle::fromDegrees(ui.spinY->value()));
    angles.setZ(Angle::fromDegrees(ui.spinZ->value()));
    //auto command = CTransform(TransformRotate(angles));
    //modelViewer->execute(command);
}

void MainWindow::onAddCamera() {
    //modelViewer->execute(CAddCamera());
}

void MainWindow::onAddModel() {
    QString filename = QFileDialog::getOpenFileName();
    //if (!filename.isEmpty())
    //    modelViewer->execute(CAddModel(filename.toStdString()));
}

void MainWindow::onRemove() {
    /*modelViewer->execute(CRemoveObject(beeba));*/
}

void MainWindow::onClear() {
    modelViewer->execute(CClear());
}
