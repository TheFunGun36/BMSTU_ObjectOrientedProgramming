#pragma once
#include <qobject.h>
#include "Doors.h"
#include "Button.h"
#include "Controller.h"
#include "Timer.h"

class Cabin : public QObject {
    Q_OBJECT


signals:
    // Doors:
    void doorsClose();
    void doorsOpen();

    // Timer:
    void timerStart(int ticks);

    // Controller
    void requestDirection(int currentFloor, bool goUp);
    void requestArrival(int currentFloor);

    // Internal
    void startClosingDoors();
    void startMoving();
    void startOpeningDoors();
    void goIdle();

public slots:
    void stop();
    void setDirection(bool goUp);
    void arrived();

private slots:
    void waitDoorsClose();
    void move();
    void waitForTimer();

public:
    enum State {
        StateIdle,
        StateGettingDirection,
        StateWaitingDoorsClose,
        StateMoving,
        StateWaitingDoorsOpen,
        StateWaiting
    };
    Q_ENUM(State);

    Cabin(int floorsAmount = 2, QObject* parent = nullptr);
    void connectAll();

    inline ButtonController& controller() { return _controller; }
    inline Doors& doors() { return _doors; }
    inline Timer& timer() { return _timer; }
    inline QTimer& movementTimer() { return _movementTimer; }

    inline State state() const noexcept { return _state; }
    inline int currentFloor() const noexcept { return _floor; }
    inline bool goingUp() const noexcept { return _goingUp; }

private:
    State _state = StateIdle;
    Doors _doors;
    ButtonController _controller;
    Timer _timer;
    
    int _floor = 1;
    bool _goingUp = false;
    int _timerWaitTicks = 3;

    int _movementDelayMsec = 500;
    QTimer _movementTimer;
};
