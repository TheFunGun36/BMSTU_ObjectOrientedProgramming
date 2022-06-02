#pragma once
#include <qobject.h>
#include <set>

class ButtonController : public QObject {
    Q_OBJECT


signals:
    void buttonProcessed();
    void arrived();
    void goIdle();
    void setDirection(bool goUp);
    void waitForButton();

public slots:
    void idle();
    void waitButton();
    void buttonPressed(int floor, bool isInside);
    void requestDirection(int currentFloor, bool goUp);
    void requestArrival(int currentFloor);

public:
    enum class State {
        Idle,
        WaitButton,
        ProcessingButton,
        CheckDirection,
        CheckArrival
    };

    ButtonController(QObject* parent = nullptr);

private:
    State _state = State::WaitButton;
    std::set<int> _floorsToVisit;
    int _savedFloor = 1;
};
