#include "Cabin.h"

Cabin::Cabin(int floorsAmount, QObject* parent)
    : QObject(parent) {
    _movementTimer.setSingleShot(false);
    _movementTimer.setInterval(500);
}

void Cabin::processButton(int floor) {
    if (_state == StateIdle) {
        _state = StateProcessingButton;

        if (floor != _floor)
            emit requestDirection(_floor, _direction);
        else
            emit requestArrival(floor);
    }
    else if (_state == StateWaiting && floor == _floor) {
        _state = StateProcessingButton;
        emit requestArrival(floor);
    }
}

void Cabin::idle() {
    if (_state == StateMoving) {
        _state = StateIdle;
    }
    else if (_state == StateWaiting) {
        _state = StateIdle;
        emit requestDirection(_floor, _direction);
    }
    else {
        _state = StateIdle;
        if (_doors.state() != Doors::StateOpened) {
            _movementTimer.stop();
            emit startOpeningDoors();
        }
    }
}

void Cabin::move(ButtonController::Direction direction) {
    if (_state == StateIdle || _state == StateProcessingButton) {
        _state = StateMoving;
        _direction = direction;

        if (_doors.state() == Doors::StateClosed) {
            _movementTimer.start();
            emit startMoving();
        }
        else {
            emit startClosingDoors();
        }
    }
    else if (_state == StateMoving) {
        if (_direction == ButtonController::DirectionUp)
            _floor++;
        else if (_direction == ButtonController::DirectionDown)
            _floor--;

        emit requestArrival(_floor);
    }
}

void Cabin::waitForTimer() {
    _state = StateWaiting;

    if (_doors.state() == Doors::StateOpened)
        emit requestTimerStart(_timerWaitTicks);
    else if (_doors.state() != Doors::StateOpening) {
        _movementTimer.stop();
        emit startOpeningDoors();
    }
}

void Cabin::connectAll() {
    _doors.connectAll();
    _controller.connectAll();
    _timer.connectAll();

    connect(this, &Cabin::startClosingDoors, this, &Cabin::idle);
    connect(this, &Cabin::startClosingDoors, &_doors, &Doors::close);
    connect(this, &Cabin::startOpeningDoors, &_doors, &Doors::open);
    connect(this, &Cabin::requestArrival, &_controller, &ButtonController::processArrival);
    connect(this, &Cabin::requestDirection, &_controller, &ButtonController::processDirection);
    connect(this, &Cabin::requestTimerStart, &_timer, &Timer::set);
    connect(&_controller, &ButtonController::direction, this, &Cabin::move);
    connect(&_controller, &ButtonController::arrived, this, &Cabin::waitForTimer);
    connect(&_controller, &ButtonController::newButton, this, &Cabin::processButton);
    connect(&_doors, &Doors::closed, this, [this]() { move(_direction); });
    connect(&_doors, &Doors::opened, this, &Cabin::waitForTimer);
    connect(&_doors, &Doors::failToClose, this, &Cabin::idle);
    connect(&_timer, &Timer::timeout, this, &Cabin::idle);
    connect(&_movementTimer, &QTimer::timeout, this, [this]() { move(_direction); });
}
