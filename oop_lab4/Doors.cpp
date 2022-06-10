#include "Doors.h"

void Doors::open() {
    _state = StateStartOpening;
    _timer.disconnect();
    connect(&_timer, &QTimer::timeout, this, &Doors::openTick);
    _timer.start(_timerDelayMsec);
    emit startedOpening();
}

void Doors::openTick() {
    if (_state == StateStartOpening || _state == StateOpening) {
        _state = StateOpening;
        if (_blockedForOpen) {
            emit goIdle();
        }
        else if (sender() == &_timer) {
            if (!isOpen())
                _doorsDistance++;
            if (isOpen())
                emit goOpen();
            else
                emit opening();
        }
    }
}

void Doors::close() {
    _state = StateStartClosing;
    _timer.disconnect();
    connect(&_timer, &QTimer::timeout, this, &Doors::closeTick);
    _timer.start(_timerDelayMsec);
    emit startedClosing();
}

void Doors::closeTick() {
    if (_state == StateStartClosing || _state == StateClosing) {
        _state = StateClosing;
        if (_blockedForClose) {
            emit goIdle();
        }
        else if (sender() == &_timer) {
            if (!isClosed())
                _doorsDistance--;
            if (isClosed())
                emit goClosed();
            else
                emit closing();
        }
    }
}

void Doors::onOpened() {
    if (_state == StateOpening) {
        _state = StateOpened;
        _timer.stop();
        emit opened();
    }
}
void Doors::onClosed() {
    if (_state == StateClosing) {
        _state = StateClosed;
        _timer.stop();
        emit closed();
    }
}

void Doors::idle() {
    if (_state == StateOpening) {
        _state = StateBlocked;
        _timer.stop();
        emit failToOpen();
    }
    else if (_state == StateClosing) {
        _state = StateBlocked;
        _timer.stop();
        emit failToClose();
    }
}

Doors::Doors(QObject* parent)
    : QObject(parent) {
    _timer.setSingleShot(false);
}

void Doors::connectAll() {
    connect(this, &Doors::goOpen, this, &Doors::onOpened);
    connect(this, &Doors::goClosed, this, &Doors::onClosed);
    connect(this, &Doors::goIdle, this, &Doors::idle);
}
