#include "Cabin.h"

void Cabin::waitDoorsClose() {
    _state = StateWaitingDoorsClose;
    emit doorsClose();
}

void Cabin::stop() {
    _state = StateIdle;
    emit requestDirection(_floor, _goingUp);
}

void Cabin::setDirection(bool goUp) {
    _state = StateGettingDirection;
    _goingUp = goUp;
    emit startClosingDoors();
}

void Cabin::move() {
    if (_state == StateWaitingDoorsClose) {
        _state = StateMoving;
        _movementTimer.start(_movementDelayMsec);
        emit startMoving();
    }
    else if (_state == StateMoving) {
        _floor += _goingUp ? 1 : -1;

        emit requestArrival(_floor);
    }
}

void Cabin::arrived() {
    _state = StateWaitingDoorsOpen;
    _movementTimer.stop();
    emit startOpeningDoors();
    emit doorsOpen();
}

void Cabin::waitForTimer() {
    _state = StateWaiting;
    emit timerStart(_timerWaitTicks);
}

Cabin::Cabin(int floorsAmount, QObject* parent)
    : QObject(parent) {
    _movementTimer.setSingleShot(false);
}

void Cabin::connectAll() {
    _doors.connectAll();
    _controller.connectAll();
    _timer.connectAll();

    connect(this, &Cabin::doorsClose, &_doors, &Doors::close);
    connect(&_doors, &Doors::closed, this, &Cabin::move);
    connect(&_doors, &Doors::failToClose, this, &Cabin::arrived);

    connect(this, &Cabin::doorsOpen, &_doors, &Doors::open);
    connect(&_doors, &Doors::opened, this, &Cabin::waitForTimer);
    connect(&_doors, &Doors::failToOpen, this, &Cabin::stop);

    connect(this, &Cabin::timerStart, &_timer, &Timer::set);
    connect(&_timer, &Timer::timeout, this, &Cabin::goIdle);

    connect(this, &Cabin::requestDirection, &_controller, &ButtonController::requestDirection);
    connect(this, &Cabin::requestArrival, &_controller, &ButtonController::requestArrival);
    connect(&_controller, &ButtonController::arrived, this, &Cabin::arrived);
    connect(&_controller, &ButtonController::setDirection, this, &Cabin::setDirection);

    connect(this, &Cabin::startClosingDoors, this, &Cabin::waitDoorsClose);
    connect(this, &Cabin::startMoving, this, &Cabin::move);
    connect(this, &Cabin::goIdle, this, &Cabin::stop);

    connect(&_movementTimer, &QTimer::timeout, this, &Cabin::move);
}
