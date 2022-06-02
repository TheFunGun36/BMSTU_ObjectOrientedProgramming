#include "Timer.h"

void Timer::set(int ticks) {
    if (_state == State::Idle) {
        _state = State::Set;
        _ticks = ticks;
        _timer.start(_timerDelayMsec);
    }
}

void Timer::reset() {
    _state = State::Idle;
    _ticks = 0;
    _timer.stop();
}

void Timer::onTick() {
    if (_state == State::Set)
        _state = State::Ticking;

    if (_state == State::Ticking) {
        _ticks--;

        if (!_ticks) {
            _timer.stop();
            emit timeout();
        }
        else {
            emit tick();
        }
    }
}

Timer::Timer(int timerDelayMsec, QObject* parent)
    : QObject(parent)
    , _timerDelayMsec(timerDelayMsec) {
    _timer.setSingleShot(false);
    connect(&_timer, &QTimer::timeout, this, &Timer::onTick);
    connect(this, &Timer::timeout, this, &Timer::reset);
}

