#include "mainwindow.h"
#include <qlabel.h>
#include <qpushbutton.h>
#include <qvalidator.h>
#include <qmessagebox.h>
#include <qmenu.h>
#include <qmenubar.h>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include "FileParse.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    userData = new wireframe::UserData;
    userData->isPerspective = false;
    userData->cameraDistance = 100;

    setCentralWidget(new QWidget(this));

    canvas = new Canvas(this);
    canvas->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    canvas->setMinimumSize(600, 400);

    auto layout = new QHBoxLayout(this);
    auto leftPanel = new QVBoxLayout(this);

    centralWidget()->setLayout(layout);

    createMoveSection(leftPanel);
    leftPanel->addSpacerItem(new QSpacerItem(0, 20));
    createScaleSection(leftPanel);
    leftPanel->addSpacerItem(new QSpacerItem(0, 20));
    createRotateSection(leftPanel);

    leftPanel->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));

    layout->addLayout(leftPanel);
    layout->addWidget(canvas);

    createMenu();
}

MainWindow::~MainWindow() {
    delete userData;
}

void MainWindow::createMoveSection(QVBoxLayout *layout) {
    QLabel *title = new QLabel("Перенос", this);
    title->setFont(QFont("Calibri", 18));
    layout->addWidget(title);

    spinMoveDx = new QDoubleSpinBox(this);
    spinMoveDy = new QDoubleSpinBox(this);
    spinMoveDz = new QDoubleSpinBox(this);
    spinMoveDx->setRange(-500, 500);
    spinMoveDy->setRange(-500, 500);
    spinMoveDz->setRange(-500, 500);

    layout->addWidget(new QLabel("Вектор смещения:", this));
    auto layoutData = new QHBoxLayout(this);
    layoutData->addWidget(spinMoveDx);
    layoutData->addWidget(spinMoveDy);
    layoutData->addWidget(spinMoveDz);

    layout->addLayout(layoutData);

    QPushButton *apply = new QPushButton("Перенести", this);
    connect(apply, &QPushButton::clicked, this, &MainWindow::moveModel);
    apply->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    layout->addWidget(apply);
};

void MainWindow::createScaleSection(QVBoxLayout *layout) {
    QLabel *title = new QLabel("Масштаб", this);
    title->setFont(QFont("Calibri", 18));
    layout->addWidget(title);

    spinScaleKx = new QDoubleSpinBox(this);
    spinScaleKy = new QDoubleSpinBox(this);
    spinScaleKz = new QDoubleSpinBox(this);
    spinScaleKx->setRange(-50, 50);
    spinScaleKy->setRange(-50, 50);
    spinScaleKz->setRange(-50, 50);
    spinScaleCenterX = new QDoubleSpinBox(this);
    spinScaleCenterY = new QDoubleSpinBox(this);
    spinScaleCenterZ = new QDoubleSpinBox(this);
    spinScaleCenterX->setRange(-500, 500);
    spinScaleCenterY->setRange(-500, 500);
    spinScaleCenterZ->setRange(-500, 500);

    layout->addWidget(new QLabel("Коэффициенты масштабирования:", this));
    auto layoutData = new QHBoxLayout(this);
    layoutData->addWidget(spinScaleKx);
    layoutData->addWidget(spinScaleKy);
    layoutData->addWidget(spinScaleKz);

    layout->addLayout(layoutData);

    layout->addWidget(new QLabel("Центр масштабирования:", this));
    auto layoutCenter = new QHBoxLayout(this);
    layoutCenter->addWidget(spinScaleCenterX);
    layoutCenter->addWidget(spinScaleCenterY);
    layoutCenter->addWidget(spinScaleCenterZ);
    layout->addLayout(layoutCenter);

    QPushButton *apply = new QPushButton("Масштабировать", this);
    connect(apply, &QPushButton::clicked, this, &MainWindow::scaleModel);
    apply->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    layout->addWidget(apply);
};

void MainWindow::createRotateSection(QVBoxLayout *layout) {
    QLabel *title = new QLabel("Поворот", this);
    title->setFont(QFont("Calibri", 18));
    layout->addWidget(title);

    spinRotateAngleX = new QDoubleSpinBox(this);
    spinRotateAngleY = new QDoubleSpinBox(this);
    spinRotateAngleZ = new QDoubleSpinBox(this);
    spinRotateAngleX->setRange(-360, 360);
    spinRotateAngleY->setRange(-360, 360);
    spinRotateAngleZ->setRange(-360, 360);
    spinRotateCenterX = new QDoubleSpinBox(this);
    spinRotateCenterY = new QDoubleSpinBox(this);
    spinRotateCenterZ = new QDoubleSpinBox(this);
    spinRotateCenterX->setRange(-500, 500);
    spinRotateCenterY->setRange(-500, 500);
    spinRotateCenterZ->setRange(-500, 500);

    layout->addWidget(new QLabel("Углы вращения относительно осей:", this));
    auto layoutAngles = new QHBoxLayout(this);
    layoutAngles->addWidget(spinRotateAngleX);
    layoutAngles->addWidget(spinRotateAngleY);
    layoutAngles->addWidget(spinRotateAngleZ);
    layout->addLayout(layoutAngles);

    layout->addWidget(new QLabel("Центр поворота:", this));
    auto layoutCenter = new QHBoxLayout(this);
    layoutCenter->addWidget(spinRotateCenterX);
    layoutCenter->addWidget(spinRotateCenterY);
    layoutCenter->addWidget(spinRotateCenterZ);
    layout->addLayout(layoutCenter);

    QPushButton *apply = new QPushButton("Повернуть", this);
    connect(apply, &QPushButton::clicked, this, &MainWindow::rotateModel);
    apply->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    layout->addWidget(apply);
}

void MainWindow::createMenu() {
    actionFileOpen = new QAction("Открыть", this);
    actionFileOpen->setShortcut(QKeySequence::Open);
    actionFileOpen->setStatusTip("Открыть файл с 3D моделью");
    connect(actionFileOpen, &QAction::triggered, this, &MainWindow::fileOpen);

    actionFileSave = new QAction("Сохранить", this);
    actionFileSave->setShortcut(QKeySequence::Save);
    actionFileSave->setStatusTip("Сохранить изменения");
    actionFileSave->setDisabled(true);
    connect(actionFileSave, &QAction::triggered, this, &MainWindow::fileSave);

    actionFileSaveAs = new QAction("Сохранить как...", this);
    actionFileSaveAs->setShortcut(QKeySequence::SaveAs);
    actionFileSaveAs->setStatusTip("Сохранить файл с 3D моделью");
    actionFileSaveAs->setDisabled(true);
    connect(actionFileSaveAs, &QAction::triggered, this, &MainWindow::fileSaveAs);

    QMenu *fileMenu = menuBar()->addMenu("Файл");
    fileMenu->addAction(actionFileOpen);
    fileMenu->addAction(actionFileSave);
    fileMenu->addAction(actionFileSaveAs);

    actionModelPerspective = new QAction("Переключить перспективу", this);
    actionModelPerspective->setShortcut(QKeySequence::Print);
    actionModelPerspective->setStatusTip("Переключить между перспективным режимом проекции и ортогональным");
    actionModelPerspective->setDisabled(true);
    connect(actionModelPerspective, &QAction::triggered, this, [this]() {
        using namespace wireframe;
        perspective = !perspective;
        updateModel();
        });

    QMenu *modelMenu = menuBar()->addMenu("Модель");
    modelMenu->addAction(actionModelPerspective);
}

void MainWindow::fileOpen() {
    using namespace wireframe;
    QFileDialog fileDialog(this);
    QString filename = fileDialog.getOpenFileName(this);
    if (!filename.isEmpty()) {
        userData->filename = filename;
        ExitCode exitCode = processEntry(*userData, Command::fileLoad);

        if (exitCode != ExitCode::ok) {
            QMessageBox::critical(this, "Ошибка", getErrorMessage(exitCode, userData->fileLineFailed));
        }
        else {
            perspective = false;
            updateModel();
            currentFilename = filename;
            actionFileSave->setEnabled(true);
            actionFileSaveAs->setEnabled(true);
            actionModelPerspective->setEnabled(true);
        }
    }
}

void MainWindow::fileSave() {
    using namespace wireframe;
    ExitCode exitCode = processEntry(*userData, Command::fileSave);

    if (exitCode != ExitCode::ok) {
        QMessageBox::critical(this, "Ошибка", getErrorMessage(exitCode));
    }
}

void MainWindow::fileSaveAs() {
    using namespace wireframe;
    QFileDialog fileDialog(this);
    QString filename = fileDialog.getSaveFileName(this);
    if (!filename.isEmpty()) {
        userData->filename = filename;
        ExitCode exitCode = processEntry(*userData, Command::fileSave);

        if (exitCode != ExitCode::ok) {
            QMessageBox::critical(this, "Ошибка", getErrorMessage(exitCode));
        }
        else {
            currentFilename = filename;
        }
    }
}

void MainWindow::moveModel() {
    using namespace wireframe;
    userData->moveVector.setX(spinMoveDx->value());
    userData->moveVector.setY(spinMoveDy->value());
    userData->moveVector.setZ(spinMoveDz->value());
    ExitCode exitCode = processEntry(*userData, Command::modelMove);
    updateModel();
}

void MainWindow::scaleModel() {
    using namespace wireframe;
    userData->scaleCoeficients.setX(spinScaleKx->value());
    userData->scaleCoeficients.setY(spinScaleKy->value());
    userData->scaleCoeficients.setZ(spinScaleKz->value());
    userData->scalePoint.setX(spinScaleCenterX->value());
    userData->scalePoint.setY(spinScaleCenterY->value());
    userData->scalePoint.setZ(spinScaleCenterZ->value());
    ExitCode exitCode = processEntry(*userData, Command::modelScale);
    updateModel();
}

void MainWindow::rotateModel() {
    using namespace wireframe;
    userData->rotatePoint.setX(spinRotateCenterX->value());
    userData->rotatePoint.setY(spinRotateCenterY->value());
    userData->rotatePoint.setZ(spinRotateCenterZ->value());
    userData->rotateAngles.setX(qDegreesToRadians(spinRotateAngleX->value()));
    userData->rotateAngles.setY(qDegreesToRadians(spinRotateAngleY->value()));
    userData->rotateAngles.setZ(qDegreesToRadians(spinRotateAngleZ->value()));
    ExitCode exitCode = processEntry(*userData, Command::modelRotate);
    updateModel();
}

void MainWindow::updateModel() {
    if (!canvas->setModel(userData->model, perspective)) {
        QMessageBox::warning(this, "Модель", "Координата Z вышла за пределы перспективной камеры. "
            "Режим проекции снова установлен в ортогональный");
        perspective = false;
        canvas->setModel(userData->model, perspective);
    }
}
