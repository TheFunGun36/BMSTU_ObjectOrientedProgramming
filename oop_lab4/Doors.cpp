#include "Doors.h"

void Doors::open() {
    if (_state == StateIdle) {
        _state = StateOpening;
        connect(&_timer, &QTimer::timeout, this, &Doors::open);
        _timer.start(_timerDelayMsec);
    }
    else if (_state == StateOpening) {
        if (isOpen()) {
            _timer.stop();
            emit opened();
        }
        else if (_blockedForOpen) {
            _timer.stop();
            emit failToOpen();
        }
        else {
            _doorsDistance++;
            emit opening();
        }
    }
}

void Doors::close() {
    if (_state == StateIdle) {
        _state = StateClosing;
        connect(&_timer, &QTimer::timeout, this, &Doors::close);
        _timer.start(_timerDelayMsec);
    }
    else if (_state == StateClosing) {
        if (isClosed()) {
            _timer.stop();
            emit closed();
        }
        else if (_blockedForClose) {
            _timer.stop();
            emit failToClose();
        }
        else {
            _doorsDistance--;
            emit closing();
        }
    }
}

void Doors::idle() {
    _state = StateIdle;
    _timer.disconnect();
    _timer.stop();
}

Doors::Doors(QObject* parent)
    : QObject(parent) {
    _timer.setSingleShot(false);
}

void Doors::connectAll() {
    connect(this, &Doors::opened, this, &Doors::idle);
    connect(this, &Doors::closed, this, &Doors::idle);
    connect(this, &Doors::failToOpen, this, &Doors::idle);
    connect(this, &Doors::failToClose, this, &Doors::idle);
}
