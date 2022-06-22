#include "mainwindow.h"
#include "itemrow.h"
#include "Painter.h"
#include "../model/jinitializationmanager.h"
#include "../model/jinitializationmanagercommands.h"
#include "../model/jtransformaction.h"
#include "../model/jrenderercommands.h"
#include "../model/jscenemanagercommands.h"
#include <qfiledialog.h>

using namespace Jora;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent) {
    ui.setupUi(this);

    InitializationManager im;
    modelViewer = im.createModelViewer();

    connect(ui.actionAddModel, &QAction::triggered, this, &MainWindow::onAddModel);
    connect(ui.widget, &Canvas::paint, this, &MainWindow::upd);
    connect(ui.moveBtn, &QPushButton::pressed, this, &MainWindow::onMove);
    connect(ui.scaleBtn, &QPushButton::pressed, this, &MainWindow::onScale);
    connect(ui.rotateBtn, &QPushButton::pressed, this, &MainWindow::onRotate);

    std::shared_ptr<ObjectId> id = std::make_shared<ObjectId>();
    modelViewer->execute(CAddCamera(id));
    auto* item = new QListWidgetItem(QString("Camera, id=%0").arg(*id), ui.list);
    ui.list->addItem(item);
    modelViewer->execute(CTransform(std::make_unique<TransformMove>(TransformMove(Vector3D(0, 0, -100))), *id));
    modelViewer->execute(CSetActiveCamera(*id));
}

void MainWindow::onMove() {
    Vector3D shift;
    shift.setX(ui.spinX->value());
    shift.setY(ui.spinY->value());
    shift.setZ(ui.spinZ->value());
    auto command = CTransform(std::make_unique<TransformMove>(shift), currentObject());
    modelViewer->execute(std::move(command));
    ui.widget->update();
}

void MainWindow::onScale() {
    Vector3D scale;
    scale.setX(ui.spinX->value());
    scale.setY(ui.spinY->value());
    scale.setZ(ui.spinZ->value());
    auto command = CTransform(std::make_unique<TransformScale>(scale), currentObject());
    modelViewer->execute(std::move(command));
    ui.widget->update();
}

void MainWindow::onRotate() {
    EulerAngles angles;
    angles.setX(Angle::fromDegrees(ui.spinX->value()));
    angles.setY(Angle::fromDegrees(ui.spinY->value()));
    angles.setZ(Angle::fromDegrees(ui.spinZ->value()));
    auto command = CTransform(std::make_unique<TransformRotate>(angles), currentObject());
    modelViewer->execute(std::move(command));
    ui.widget->update();
}

void MainWindow::onAddCamera() {
    std::shared_ptr<ObjectId> id = std::make_shared<ObjectId>();
    modelViewer->execute(CAddCamera(id));
    auto* item = new QListWidgetItem(QString("Camera, id=%0").arg(*id), ui.list);
    ui.list->addItem(item);
    ui.widget->update();
}

void MainWindow::onAddModel() {
    QString filename = QFileDialog::getOpenFileName();
    if (!filename.isEmpty()) {
        std::shared_ptr<ObjectId> id = std::make_shared<ObjectId>();
        modelViewer->execute(CAddModel(filename.toStdString(), id));
        auto* item = new QListWidgetItem(QString("Model, id=%0").arg(*id), ui.list);
        ui.list->addItem(item);
    }
    ui.widget->update();
}

void MainWindow::onRemove() {
    modelViewer->execute(CRemoveObject(currentObject()));
    ui.widget->update();
}

void MainWindow::onClear() {
    modelViewer->execute(CClear());
    ui.widget->update();
}

void MainWindow::upd(QPainter& qp) {
    auto ptr = std::make_shared<QtPainter>(QtPainter(qp));
    modelViewer->execute(CUpdateCamera(ui.widget->width(), ui.widget->height(), fov));
    modelViewer->execute(CRender(ptr));
}

Jora::ObjectId MainWindow::currentObject() {
    Jora::ObjectId result = 0;

    auto current = ui.list->currentItem();
    if (current) {
        auto list = current->text().split('=');
        auto last = list.last();
        result = last.toInt();
    }

    return result;
}
