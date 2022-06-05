#include "MainWindow.h"
#include <QMetaEnum>
#include <qscrollbar.h>
#include <qfile.h>
#include <qmessagebox.h>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , _cabin(8) {
    ui.setupUi(this);

    for (int i = 0; i < 8; i++)
        _buttons[i] = new Button(i + 1, false, this);

    setDarkTheme();
    connectLogs();
    connectButtons();
    _cabin.connectAll();
    connect(ui.checkBox, &QCheckBox::clicked, this, [this](bool blocked) {
        if (blocked)
            _cabin.doors().blockClose();
        else
            _cabin.doors().unblockClose(); });
    connect(ui.btnClear, &QPushButton::pressed, ui.eventList, &QListWidget::clear);
    update();

    wow.reserve(4);
    for (int i = 0; i < 4; i++)
        wow.enqueue(0);
}

void MainWindow::buttonPressed(int index) {
    addToHistory(QString("[КНОПКА %1] нажата").arg(index + 1));
    _buttons[index]->press();

    wow.dequeue();
    wow.enqueue(index);
    checkWow();
}

template<typename QEnum>
QString qtEnumToString(const QEnum value) {
    return QMetaEnum::fromType<QEnum>().valueToKey(value);
}

void MainWindow::update() {
    ui.lcdNumber->display(_cabin.currentFloor());
    ui.progressL->setValue(5 - _cabin.doors().distance());
    ui.progressR->setValue(5 - _cabin.doors().distance());
    
    auto& t = _cabin.controller().floorsToVisit();
    ui.btn1->setText(QString(t.find(1) != t.end() ? "[1]" : "1"));
    ui.btn2->setText(QString(t.find(2) != t.end() ? "[2]" : "2"));
    ui.btn3->setText(QString(t.find(3) != t.end() ? "[3]" : "3"));
    ui.btn4->setText(QString(t.find(4) != t.end() ? "[4]" : "4"));
    ui.btn5->setText(QString(t.find(5) != t.end() ? "[5]" : "5"));
    ui.btn6->setText(QString(t.find(6) != t.end() ? "[6]" : "6"));
    ui.btn7->setText(QString(t.find(7) != t.end() ? "[7]" : "7"));
    ui.btn8->setText(QString(t.find(8) != t.end() ? "[8]" : "8"));
}

void MainWindow::addToHistory(QString text) {
    bool shouldScroll = ui.eventList->verticalScrollBar()->maximum() == ui.eventList->verticalScrollBar()->value();
    auto* lastItem = ui.eventList->item(ui.eventList->count() - 1);
    if (lastItem && lastItem->text().startsWith(text)) {
        lastItem->setText(lastItem->text() + ".");
    }
    else {
        ui.eventList->addItem(new QListWidgetItem(text, ui.eventList));
        if (shouldScroll)
            ui.eventList->scrollToBottom();
    }
    update();
}

void MainWindow::setDarkTheme() {
    QFile file(":/MainWindow/StyleSheet.css");
    file.open(QFile::ReadOnly);
    setStyleSheet(file.readAll());
    file.close();
}

void MainWindow::connectLogs() {
    connect(ui.btn1, &QPushButton::pressed, this, [this]() { buttonPressed(0); });
    connect(ui.btn2, &QPushButton::pressed, this, [this]() { buttonPressed(1); });
    connect(ui.btn3, &QPushButton::pressed, this, [this]() { buttonPressed(2); });
    connect(ui.btn4, &QPushButton::pressed, this, [this]() { buttonPressed(3); });
    connect(ui.btn5, &QPushButton::pressed, this, [this]() { buttonPressed(4); });
    connect(ui.btn6, &QPushButton::pressed, this, [this]() { buttonPressed(5); });
    connect(ui.btn7, &QPushButton::pressed, this, [this]() { buttonPressed(6); });
    connect(ui.btn8, &QPushButton::pressed, this, [this]() { buttonPressed(7); });

    connectLogsCabin();
    connectLogsDoors();
    connectLogsController();
    connectLogsTimer();
}

void MainWindow::connectLogsCabin() {
    connect(&_cabin, &Cabin::requestArrival, this, [this](bool) {
        addToHistory(QString("[КАБИНА] запрос прибытия")); });
    connect(&_cabin, &Cabin::requestDirection, this, [this](int, ButtonController::Direction) {
        addToHistory(QString("[КАБИНА] запрос направления")); });
    connect(&_cabin, &Cabin::startMoving, this, [this]() {
        addToHistory(QString("[КАБИНА] начало движения")); });
    connect(&_cabin, &Cabin::startClosingDoors, this, [this]() {
        addToHistory(QString("[КАБИНА] запрос закрытия дверей")); });
    connect(&_cabin, &Cabin::startOpeningDoors, this, [this]() {
        addToHistory(QString("[КАБИНА] запрос открытия дверей")); });
}

void MainWindow::connectLogsDoors() {
    connect(&_cabin.doors(), &Doors::opened, this, [this]() {
        addToHistory(QString("[ДВЕРИ] открылись")); });
    connect(&_cabin.doors(), &Doors::closed, this, [this]() {
        addToHistory(QString("[ДВЕРИ] закрылись")); });
    connect(&_cabin.doors(), &Doors::failToOpen, this, [this]() {
        addToHistory(QString("[ДВЕРИ] не открылись")); });
    connect(&_cabin.doors(), &Doors::failToClose, this, [this]() {
        addToHistory(QString("[ДВЕРИ] не закрылись")); });
    connect(&_cabin.doors(), &Doors::opening, this, [this]() {
        addToHistory(QString("[ДВЕРИ] открываются")); });
    connect(&_cabin.doors(), &Doors::closing, this, [this]() {
        addToHistory(QString("[ДВЕРИ] закрываются")); });
}

void MainWindow::connectLogsController() {
    connect(&_cabin.controller(), &ButtonController::arrived, this, [this]() {
        addToHistory(QString("[КОНТРОЛЛЕР] подтверждение прибытия")); });
    connect(&_cabin.controller(), &ButtonController::direction, this, [this](ButtonController::Direction) {
        addToHistory(QString("[КОНТРОЛЛЕР] подтверждение направления")); });
    connect(&_cabin.controller(), &ButtonController::newButton, this, [this]() {
        addToHistory(QString("[КОНТРОЛЛЕР] подтверждение нажатия кнопки")); });
}

void MainWindow::connectLogsTimer() {
    connect(&_cabin.timer(), &Timer::tick, this, [this]() {
        addToHistory(QString("[ТАЙМЕР] отсчёт времени")); });
    connect(&_cabin.timer(), &Timer::timeout, this, [this]() {
        addToHistory(QString("[ТАЙМЕР] завершение отсчёта времени")); });
}

void MainWindow::connectButtons() {
    for (int i = 0; i < 8; i++)
        connect(_buttons[i], &Button::pressed, &_cabin.controller(), &ButtonController::processButton);
}

void MainWindow::checkWow() {
    if (wow[0] == 0 &&
        wow[1] == 2 &&
        wow[2] == 2 &&
        wow[3] == 6) {
        QMessageBox::critical(this, "OMG", "1337, OMGOMGOMG WOOOOW OMGOMGOMG WOOOOW OMGOMGOMG WOOOOW OMGOMGOMG WOOOOW OMGOMGOMG WOOOOW OMGOMGOMG WOOOOW OMGOMGOMG WOOOOW OMGOMGOMG WOOOOW OMGOMGOMG WOOOOW OMGOMGOMG WOOOOW OMGOMGOMG WOOOOW OMGOMGOMG WOOOOW OMGOMGOMG WOOOOW OMGOMGOMG WOOOOW OMGOMGOMG WOOOOW OMGOMGOMG WOOOOW OMGOMGOMG WOOOOW OMGOMGOMG WOOOOW OMGOMGOMG WOOOOW OMGOMGOMG WOOOOW OMGOMGOMG WOOOOW OMGOMGOMG WOOOOW");
    }
}
