#include "Doors.h"

void Doors::open() {
    if (_state == StateOpened) {
        emit opened();
    }
    else if (_state == StateOpening) {
        if (isOpen()) {
            emit opened();
        }
        else if (_blockedForOpen) {
            emit failToOpen();
        }
        else if (sender() == &_timer) {
            _doorsDistance++;
            emit opening();
        }
    }
    else {
        _state = StateOpening;
        _timer.disconnect();
        connect(&_timer, &QTimer::timeout, this, &Doors::open);
        _timer.start(_timerDelayMsec);
    }
}

void Doors::close() {
    if (_state == StateClosed) {
        emit closed();
    }
    else if (_state == StateClosing) {
        if (isClosed()) {
            emit closed();
        }
        else if (_blockedForClose) {
            emit failToClose();
        }
        else if (sender() == &_timer) {
            _doorsDistance--;
            emit closing();
        }
    }
    else {
        _state = StateClosing;
        _timer.disconnect();
        connect(&_timer, &QTimer::timeout, this, &Doors::close);
        _timer.start(_timerDelayMsec);
    }
}

void Doors::onOpened() {
    _state = StateOpened;
    _timer.stop();
}
void Doors::onClosed() {
    _state = StateClosed;
    _timer.stop();
}

void Doors::idle() {
    _state = StateBlocked;
    _timer.stop();
}

Doors::Doors(QObject* parent)
    : QObject(parent) {
    _timer.setSingleShot(false);
}

void Doors::connectAll() {
    connect(this, &Doors::opened, this, &Doors::onOpened);
    connect(this, &Doors::closed, this, &Doors::onClosed);
    connect(this, &Doors::failToOpen, this, &Doors::idle);
    connect(this, &Doors::failToClose, this, &Doors::idle);
}
