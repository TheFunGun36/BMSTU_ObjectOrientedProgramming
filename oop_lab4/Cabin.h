#pragma once
#include <qobject.h>
#include "Doors.h"
#include "Button.h"
#include "Controller.h"
#include "Timer.h"

class Cabin : public QObject {
    Q_OBJECT


signals:
    void requestArrival(int floor);
    void requestDirection(int floor, ButtonController::Direction direction);
    void requestTimerStart(int ticks);
    void startMoving();

    void startOpeningDoors();
    void startClosingDoors();

private slots:
    void idle();
    void move(ButtonController::Direction direction);
    void waitForTimer();
    void processButton(int floor);

public:
    enum State {
        StateIdle,
        StateWaiting,
        StateMoving,
        StateProcessingButton
    };
    Q_ENUM(State);

    Cabin(int floorsAmount = 2, QObject* parent = nullptr);
    void connectAll();

    inline ButtonController& controller() { return _controller; }
    inline Doors& doors() { return _doors; }
    inline Timer& timer() { return _timer; }

    inline int currentFloor() const noexcept { return _floor; }
    inline ButtonController::Direction direction() const noexcept { return _direction; }

private:
    State _state = StateIdle;
    Doors _doors;
    ButtonController _controller;
    Timer _timer;
    
    int _floor = 1;
    ButtonController::Direction _direction;
    int _timerWaitTicks = 6;

    QTimer _movementTimer;
};
