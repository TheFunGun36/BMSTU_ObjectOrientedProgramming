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

    setCentralWidget(new QWidget(this));

    canvas = new Canvas(this);
    canvas->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    canvas->setMinimumSize(750, 600);

    auto layout = new QHBoxLayout(this);
    auto leftPanel = new QVBoxLayout(this);

    centralWidget()->setLayout(layout);

    createMoveSection(leftPanel);
    leftPanel->addSpacerItem(new QSpacerItem(0, 20));
    createScaleSection(leftPanel);
    leftPanel->addSpacerItem(new QSpacerItem(0, 20));
    createRotateSection(leftPanel);
    leftPanel->addSpacerItem(new QSpacerItem(0, 20));

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
    //spinMoveDx->setFixedWidth(70);
    //spinMoveDy->setFixedWidth(70);
    //spinMoveDz->setFixedWidth(70);
    //spinMoveDx->setPlaceholderText("x");
    //spinMoveDy->setPlaceholderText("y");
    //spinMoveDz->setPlaceholderText("z");

    layout->addWidget(new QLabel("Вектор смещения:", this));
    auto layoutData = new QHBoxLayout(this);
    layoutData->addWidget(spinMoveDx);
    layoutData->addWidget(spinMoveDy);
    layoutData->addWidget(spinMoveDz);

    layout->addLayout(layoutData);

    QPushButton *apply = new QPushButton("Перенести", this);
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
    spinScaleCenterX = new QDoubleSpinBox(this);
    spinScaleCenterY = new QDoubleSpinBox(this);
    spinScaleCenterZ = new QDoubleSpinBox(this);
    //spinScaleKx->setFixedWidth(70);
    //spinScaleKy->setFixedWidth(70);
    //spinScaleKz->setFixedWidth(70);
    //spinScaleCenterX->setFixedWidth(70);
    //spinScaleCenterY->setFixedWidth(70);
    //spinScaleCenterZ->setFixedWidth(70);
    //spinScaleKx->setPlaceholderText("x");
    //spinScaleKy->setPlaceholderText("y");
    //spinScaleKz->setPlaceholderText("z");
    //spinScaleCenterX->setPlaceholderText("x");
    //spinScaleCenterY->setPlaceholderText("y");
    //spinScaleCenterZ->setPlaceholderText("z");

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
    spinRotateCenterX = new QDoubleSpinBox(this);
    spinRotateCenterY = new QDoubleSpinBox(this);
    spinRotateCenterZ = new QDoubleSpinBox(this);
    //spinRotateCenterX->setFixedWidth(70);
    //spinRotateCenterY->setFixedWidth(70);
    //spinRotateCenterZ->setFixedWidth(70);
    //lineRotateAngle->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    //spinRotateCenterX->setPlaceholderText("x");
    //spinRotateCenterY->setPlaceholderText("y");
    //spinRotateCenterZ->setPlaceholderText("z");

    layout->addWidget(new QLabel("Углы вращения относительно осей:", this));
    layout->addWidget(spinRotateAngleX);
    layout->addWidget(spinRotateAngleY);
    layout->addWidget(spinRotateAngleZ);

    layout->addWidget(new QLabel("Центр поворота:", this));
    auto layoutCenter = new QHBoxLayout(this);
    layoutCenter->addWidget(spinRotateCenterX);
    layoutCenter->addWidget(spinRotateCenterY);
    layoutCenter->addWidget(spinRotateCenterZ);
    layout->addLayout(layoutCenter);

    QPushButton *apply = new QPushButton("Повернуть", this);
    apply->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    layout->addWidget(apply);
}

void MainWindow::createMenu() {
    auto fileMenu = menuBar()->addMenu("File");

    QAction *fileOpen = new QAction("Открыть", this);
    fileOpen->setShortcut(QKeySequence::Open);
    fileOpen->setStatusTip("Открыть файл с 3D моделью");
    connect(fileOpen, &QAction::triggered, this, &MainWindow::fileOpen);

    QAction *fileSave = new QAction("Сохранить", this);
    fileSave->setShortcut(QKeySequence::Save);
    fileSave->setStatusTip("Сохранить изменения");
    connect(fileSave, &QAction::triggered, this, &MainWindow::fileSave);

    QAction *fileSaveAs = new QAction("Сохранить как...", this);
    fileSaveAs->setShortcut(QKeySequence::SaveAs);
    fileSaveAs->setStatusTip("Сохранить файл с 3D моделью");
    connect(fileSaveAs, &QAction::triggered, this, &MainWindow::fileSaveAs);

    fileMenu->addAction(fileOpen);
    fileMenu->addAction(fileSave);
    fileMenu->addAction(fileSaveAs);
}

void MainWindow::fileOpen() {
    QFileDialog fileDialog(this);
    QString filename = fileDialog.getOpenFileName();
    if (filename != "<NULL>") {
        Model3D model;
        wireframe::ExitCode exitCode = wireframe::processEntry(wireframe::Command::fileLoad, *userData);

        if (exitCode != wireframe::ExitCode::ok) {
            QMessageBox::critical(this, "Ошибка", wireframe::getErrorMessage(exitCode, userData->fileLineFailed));
        }
    }
}

void MainWindow::fileSave() {
    qDebug() << "save";
}

void MainWindow::fileSaveAs() {
    qDebug() << "save as";
}
