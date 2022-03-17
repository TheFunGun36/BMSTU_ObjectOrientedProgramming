#include "MainWindow.hpp"
#include <qlabel.h>
#include <qpushbutton.h>
#include <qvalidator.h>
#include <qmessagebox.h>
#include <qmenu.h>
#include <qmenubar.h>
#include <qfiledialog.h>
#include <qmessagebox.h>

#include "ExecuteCmd.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    cameraDistance = 400;

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
    UserOutput uOut;
    executeCommand(uOut, userInput(), Command::uninitialize);
}

void MainWindow::createMoveSection(QVBoxLayout *layout) {
    QLabel *title = new QLabel("Перенос", this);
    title->setFont(QFont("Calibri", 18));
    layout->addWidget(title);

    spinMoveX = new QDoubleSpinBox(this);
    spinMoveY = new QDoubleSpinBox(this);
    spinMoveZ = new QDoubleSpinBox(this);
    spinMoveX->setRange(-500, 500);
    spinMoveY->setRange(-500, 500);
    spinMoveZ->setRange(-500, 500);

    layout->addWidget(new QLabel("Вектор смещения:", this));
    auto layoutData = new QHBoxLayout(this);
    layoutData->addWidget(spinMoveX);
    layoutData->addWidget(spinMoveY);
    layoutData->addWidget(spinMoveZ);

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

    spinScaleX = new QDoubleSpinBox(this);
    spinScaleY = new QDoubleSpinBox(this);
    spinScaleZ = new QDoubleSpinBox(this);
    spinScaleX->setRange(-50, 50);
    spinScaleY->setRange(-50, 50);
    spinScaleZ->setRange(-50, 50);

    layout->addWidget(new QLabel("Коэффициенты масштабирования:", this));
    auto layoutData = new QHBoxLayout(this);
    layoutData->addWidget(spinScaleX);
    layoutData->addWidget(spinScaleY);
    layoutData->addWidget(spinScaleZ);

    layout->addLayout(layoutData);

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

    layout->addWidget(new QLabel("Углы вращения относительно осей:", this));
    auto layoutAngles = new QHBoxLayout(this);
    layoutAngles->addWidget(spinRotateAngleX);
    layoutAngles->addWidget(spinRotateAngleY);
    layoutAngles->addWidget(spinRotateAngleZ);
    layout->addLayout(layoutAngles);

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

    QMenu *fileMenu = menuBar()->addMenu("Файл");
    fileMenu->addAction(actionFileOpen);

    actionModelPerspective = new QAction("Переключить режим отображения", this);
    actionModelPerspective->setShortcut(QKeySequence::Print);
    actionModelPerspective->setStatusTip("Переключить между перспективным режимом проекции и ортогональным");
    actionModelPerspective->setDisabled(true);
    connect(actionModelPerspective, &QAction::triggered, this, &MainWindow::togglePerspective);

    actionModelUndo = new QAction("Отменить", this);
    actionModelUndo->setShortcut(QKeySequence::Undo);
    actionModelUndo->setStatusTip("Отменить последнее действие с моделью");
    actionModelUndo->setDisabled(true);
    connect(actionModelUndo, &QAction::triggered, this, &MainWindow::undo);

    QMenu *modelMenu = menuBar()->addMenu("Модель");
    modelMenu->addAction(actionModelPerspective);
    modelMenu->addAction(actionModelUndo);
}

void MainWindow::showError(Exit exitCode) {
    UserOutput uOut;
    executeCommand(uOut, userInput(exitCode), Command::getErrorMessage);
    QMessageBox::critical(this, QString("Ошибка"), QString::fromWCharArray(uOut.errorMessage));
}

void MainWindow::fileOpen() {
    UserOutput uOut;
    QFileDialog fileDialog(this);
    QString filename = fileDialog.getOpenFileName(this);
    if (!filename.isEmpty()) {
        UserOutput uOut;
        Char *cstr = new Char[filename.size() + 1];
        filename.toWCharArray(cstr);
        cstr[filename.size()] = '\0';
        UserInput uIn = userInput(cstr);
        Exit exitCode = executeCommand(uOut, uIn, Command::modelLoad);
        delete[] cstr;

        if (isOk(exitCode)) {
            perspective = false;
            updateModel();
            currentFilename = filename;
            actionModelPerspective->setEnabled(true);
            actionModelUndo->setEnabled(true);
        }
    }
}

void MainWindow::moveModel() {
    UserInput uIn;
    uIn.actionVector.x = spinMoveX->value();
    uIn.actionVector.y = spinMoveY->value();
    uIn.actionVector.z = spinMoveZ->value();

    UserOutput uOut;
    Exit exitCode = executeCommand(uOut, uIn, Command::modelMove);
    if (!isOk(exitCode))
        showError(exitCode);
    else
        updateModel();
}

void MainWindow::scaleModel() {
    UserInput uIn;
    uIn.actionVector.x = spinScaleX->value();
    uIn.actionVector.y = spinScaleY->value();
    uIn.actionVector.z = spinScaleZ->value();

    UserOutput uOut;
    Exit exitCode = executeCommand(uOut, uIn, Command::modelScale);
    if (!isOk(exitCode))
        showError(exitCode);
    else
        updateModel();
}

void MainWindow::rotateModel() {
    UserInput uIn;
    uIn.actionVector.x = qDegreesToRadians(spinRotateAngleX->value());
    uIn.actionVector.y = qDegreesToRadians(spinRotateAngleY->value());
    uIn.actionVector.z = qDegreesToRadians(spinRotateAngleZ->value());

    UserOutput uOut;
    Exit exitCode = executeCommand(uOut, uIn, Command::modelRotate);
    if (!isOk(exitCode))
        showError(exitCode);
    else
        updateModel();
}

void MainWindow::updateModel() {
    UserOutput uOut;
    Command cmd = perspective ? Command::modelProjectPerspective : Command::modelProjectOrhogonal;
    Exit exitCode = executeCommand(uOut, userInput(cameraDistance), cmd);

    if (!isOk(exitCode)) {
        showError(exitCode);

        if (perspective) {
            perspective = false;
            updateModel();
        }
    }
    else {
        canvas->updateProjection(uOut.projection);
        projectionFree(uOut.projection);
    }
}

void MainWindow::resizeEvent(QResizeEvent *e) {
    canvas->onResize();
}

void MainWindow::togglePerspective() {
    perspective = !perspective;
    updateModel();
}

void MainWindow::undo() {
    UserOutput uOut;
    Command cmd = Command::modelUndoAction;
    Exit exitCode = executeCommand(uOut, userInput(), cmd);

    if (!isOk(exitCode))
        showError(exitCode);
    else
        updateModel();
}
