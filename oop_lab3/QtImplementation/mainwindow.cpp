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
    connect(ui.actionAddCamera, &QAction::triggered, this, &MainWindow::onAddCamera);
    connect(ui.actionClear, &QAction::triggered, this, &MainWindow::onClear);
    connect(ui.actionRemove, &QAction::triggered, this, &MainWindow::onRemove);
    connect(ui.widget, &Canvas::paint, this, &MainWindow::upd);
    connect(ui.list, &QListWidget::clicked, this, &MainWindow::onUpdateSelection);

    connect(ui.posX, &QDoubleSpinBox::valueChanged, this, &MainWindow::onTransform);
    connect(ui.posY, &QDoubleSpinBox::valueChanged, this, &MainWindow::onTransform);
    connect(ui.posZ, &QDoubleSpinBox::valueChanged, this, &MainWindow::onTransform);
    connect(ui.rotX, &QDoubleSpinBox::valueChanged, this, &MainWindow::onTransform);
    connect(ui.rotY, &QDoubleSpinBox::valueChanged, this, &MainWindow::onTransform);
    connect(ui.rotZ, &QDoubleSpinBox::valueChanged, this, &MainWindow::onTransform);
    connect(ui.scaleX, &QDoubleSpinBox::valueChanged, this, &MainWindow::onTransform);
    connect(ui.scaleY, &QDoubleSpinBox::valueChanged, this, &MainWindow::onTransform);
    connect(ui.scaleZ, &QDoubleSpinBox::valueChanged, this, &MainWindow::onTransform);

    std::shared_ptr<ObjectId> id = std::make_shared<ObjectId>();
    modelViewer->execute(CAddCamera(id));
    auto* item = new QListWidgetItem(QString("Camera, id=%0").arg(*id), ui.list);
    ui.list->addItem(item);
    modelViewer->execute(CTransform(std::make_unique<TransformMove>(TransformMove(Vector3D(0, 0, -300))), *id));
    modelViewer->execute(CSetActiveCamera(*id));

    ui.list->setCurrentRow(0);
}

void MainWindow::onTransform(double) {
    Vector3D pos;
    pos.setX(ui.posX->value());
    pos.setY(ui.posY->value());
    pos.setZ(ui.posZ->value());
    EulerAngles rot;
    rot.setX(Angle::fromDegrees(ui.rotX->value()));
    rot.setY(Angle::fromDegrees(ui.rotY->value()));
    rot.setZ(Angle::fromDegrees(ui.rotZ->value()));
    Vector3D scale;
    scale.setX(ui.scaleX->value());
    scale.setY(ui.scaleY->value());
    scale.setZ(ui.scaleZ->value());

    CTransform cmd = CTransform(std::make_unique<TransformSet>(pos, rot, scale), currentObject());
    modelViewer->execute(std::move(cmd));
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
    ui.list->takeItem(ui.list->currentRow());
    ui.widget->update();
}

void MainWindow::onClear() {
    modelViewer->execute(CClear());
    ui.list->clear();
    ui.widget->update();
}

void MainWindow::onUpdateSelection(const QModelIndex& index) {
    modelViewer->execute(CSetActiveCamera(currentObject()));
    auto transform = std::make_shared<Transform>();
    modelViewer->execute(CGetTransform(transform, currentObject()));

    ui.posX->setValue(transform->position().x());
    ui.posY->setValue(transform->position().y());
    ui.posZ->setValue(transform->position().z());
    ui.rotX->setValue(transform->rotation().x().degrees());
    ui.rotY->setValue(transform->rotation().y().degrees());
    ui.rotZ->setValue(transform->rotation().z().degrees());
    ui.scaleX->setValue(transform->scale().x());
    ui.scaleY->setValue(transform->scale().y());
    ui.scaleZ->setValue(transform->scale().z());
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
