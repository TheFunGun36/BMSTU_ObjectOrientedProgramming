#include "mainwindow.h"
#include "itemrow.h"
#include "../model/jinitializationmanager.h"
#include "../model/jinitializationmanagercommands.h"
#include "../model/jtransformaction.h"
#include "../model/jinitializationmanagercommands.h"
#include "../model/jscenemanagercommands.h"
#include <qfiledialog.h>

using namespace Jora;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent) {
    ui.setupUi(this);

    InitializationManager im;
    modelViewer = im.createModelViewer();

    connect(ui.actionAddModel, &QAction::triggered, this, &MainWindow::onAddModel);
}

void MainWindow::onMove() {
    Vector3D shift;
    shift.setX(ui.spinX->value());
    shift.setY(ui.spinY->value());
    shift.setZ(ui.spinZ->value());
    auto command = CTransform(std::make_unique<TransformMove>(shift), currentObject);
    modelViewer->execute(std::move(command));
}

void MainWindow::onScale() {
    Vector3D scale;
    scale.setX(ui.spinX->value());
    scale.setY(ui.spinY->value());
    scale.setZ(ui.spinZ->value());
    auto command = CTransform(std::make_unique<TransformScale>(scale), currentObject);
    modelViewer->execute(std::move(command));
}

void MainWindow::onRotate() {
    EulerAngles angles;
    angles.setX(Angle::fromDegrees(ui.spinX->value()));
    angles.setY(Angle::fromDegrees(ui.spinY->value()));
    angles.setZ(Angle::fromDegrees(ui.spinZ->value()));
    auto command = CTransform(std::make_unique<TransformRotate>(angles), currentObject);
    modelViewer->execute(std::move(command));
}

void MainWindow::onAddCamera() {
    std::shared_ptr<ObjectId> id = std::make_shared<ObjectId>();
    modelViewer->execute(CAddCamera(id));
    ItemRow* row = new ItemRow(*id, QString("Camera"), this);
    auto* item = new QListWidgetItem(ui.list);
    ui.list->addItem(item);
    ui.list->setItemWidget(item, row);
}

void MainWindow::onAddModel() {
    QString filename = QFileDialog::getOpenFileName();
    if (!filename.isEmpty()) {
        std::shared_ptr<ObjectId> id = std::make_shared<ObjectId>();
        modelViewer->execute(CAddModel(filename.toStdString(), id));
        ItemRow* row = new ItemRow(*id, QString("Model"), this);
        auto* item = new QListWidgetItem(ui.list);
        ui.list->addItem(item);
        ui.list->setItemWidget(item, row);
    }
}

void MainWindow::onRemove() {
    modelViewer->execute(CRemoveObject(currentObject));
}

void MainWindow::onClear() {
    modelViewer->execute(CClear());
}
