#pragma once
#include <qobject.h>
#include <set>
#include <QMetaEnum>

class ButtonController : public QObject {
    Q_OBJECT


public:
    enum Direction {
        DirectionNone,
        DirectionUp,
        DirectionDown
    };
    Q_ENUM(Direction);

signals:
    void goIdle();

    void arrived();
    void direction(Direction direction);
    void newButton(int floor);

public slots:
    void processButton(int floor, bool isPriority);
    void processArrival(int floor);
    void processDirection(int floor, Direction direction);

private slots:
    void idle();

public:
    enum State {
        StateIdle,
        StateProcessingButton,
        StateProcessingArrival,
        StateProcessingDirection
    };
    Q_ENUM(State);

    ButtonController(QObject* parent = nullptr);
    void connectAll();
    inline std::set<int>& floorsToVisit() noexcept { return _floorsToVisit; }

private:
    State _state = StateIdle;
    std::set<int> _floorsToVisit;
    int _savedFloor = 1;
};
