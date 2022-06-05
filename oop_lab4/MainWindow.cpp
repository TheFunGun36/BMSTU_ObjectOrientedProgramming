#include "MainWindow.h"
#include <QMetaEnum>
#include <qscrollbar.h>
#include <qfile.h>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , _cabin(8) {
    ui.setupUi(this);

    for (int i = 0; i < 8; i++)
        _buttons[i] = new Button(i + 1, false, this);

    setDarkTheme();
    connectAll();
    _cabin.connectAll();
    update();
}

void MainWindow::buttonPressed(int index) {
    addToHistory(QString("Button %1 pressed").arg(index + 1));
    
    _buttons[index]->press();
}

template<typename QEnum>
QString qtEnumToString(const QEnum value) {
    return QMetaEnum::fromType<QEnum>().valueToKey(value);
}

void MainWindow::update() {
    ui.lineElevatorState->setText(qtEnumToString<Cabin::State>(_cabin.state()));
    ui.lineCurrentFloor->setText(QString::number(_cabin.currentFloor()));
    ui.lineDoorsState->setText(qtEnumToString<Doors::State>(_cabin.doors().state()));
    ui.openProgress->setValue(_cabin.doors().distance());
    ui.lineTimerVal->setText(QString::number(_cabin.timer().ticks()));
}

void MainWindow::addToHistory(QString string) {
    bool shouldScroll = ui.eventList->verticalScrollBar()->maximum() == ui.eventList->verticalScrollBar()->value();
    ui.eventList->addItem(new QListWidgetItem(QString(string), ui.eventList));
    if (shouldScroll)
        ui.eventList->scrollToBottom();
    update();
}

void MainWindow::setDarkTheme() {
    QFile file(":/MainWindow/StyleSheet.css");
    file.open(QFile::ReadOnly);
    setStyleSheet(file.readAll());
    file.close();
}

void MainWindow::connectAll() {
    connect(ui.btn1, &QPushButton::pressed, this, [this]() { buttonPressed(0); });
    connect(ui.btn2, &QPushButton::pressed, this, [this]() { buttonPressed(1); });
    connect(ui.btn3, &QPushButton::pressed, this, [this]() { buttonPressed(2); });
    connect(ui.btn4, &QPushButton::pressed, this, [this]() { buttonPressed(3); });
    connect(ui.btn5, &QPushButton::pressed, this, [this]() { buttonPressed(4); });
    connect(ui.btn6, &QPushButton::pressed, this, [this]() { buttonPressed(5); });
    connect(ui.btn7, &QPushButton::pressed, this, [this]() { buttonPressed(6); });
    connect(ui.btn8, &QPushButton::pressed, this, [this]() { buttonPressed(7); });

    for (int i = 0; i < 8; i++)
        connect(_buttons[i], &Button::pressed, &_cabin.controller(), &ButtonController::buttonPressed);

    connect(&_cabin, &Cabin::startClosingDoors, this, [this]() {
        addToHistory(QString("Получение направления от контроллера"));
        addToHistory(QString("Двери закрываются")); });
    connect(&_cabin, &Cabin::startMoving, this, [this]() {
        addToHistory(QString("Лифт начал движение")); });
    connect(&_cabin, &Cabin::startOpeningDoors, this, [this]() {
        addToHistory(QString("Двери открываются")); });
    connect(&_cabin, &Cabin::timerStart, this, [this](int) {
        addToHistory(QString("Ожидание")); });
    connect(&_cabin, &Cabin::requestDirection, this, [this](bool) {
        addToHistory(QString("Запрос направления от контроллера")); });

    connect(&_cabin.movementTimer(), &QTimer::timeout, this, &MainWindow::update);
    connect(&_cabin.doors(), &Doors::closing, this, &MainWindow::update);
    connect(&_cabin.doors(), &Doors::opening, this, &MainWindow::update);
    connect(&_cabin.timer(), &Timer::tick, this, &MainWindow::update);
    connect(&_cabin.timer(), &Timer::timeout, this, &MainWindow::update);

    connect(ui.checkBox, &QCheckBox::clicked, this, [this](bool blocked) {
        if (blocked)
            _cabin.doors().blockClose();
        else
            _cabin.doors().unblockClose(); });
}
