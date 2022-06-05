#include "Controller.h"

void ButtonController::idle() {
    _state = StateIdle;
}

void ButtonController::processButton(int floor, bool isPriority) {
    _state = StateProcessingButton;
    _floorsToVisit.insert(floor);
    emit newButton(floor);
}

void ButtonController::processArrival(int floor) {
    _state = StateProcessingArrival;
    auto it = _floorsToVisit.find(floor);

    if (it == _floorsToVisit.end()) {
        emit goIdle();
    }
    else {
        _floorsToVisit.erase(it);
        emit arrived();
    }
}

void ButtonController::processDirection(int floor, Direction direction) {
    _state = StateProcessingDirection;
    if (_floorsToVisit.empty()) {
        emit goIdle();
    }
    else {
        std::set<int>::iterator it = _floorsToVisit.lower_bound(floor);
        
        if (it == _floorsToVisit.end())
            emit this->direction(DirectionDown); // down, if nothing up
        else if (*it == floor)
            emit goIdle(); //same floor, stay
        else if (it == _floorsToVisit.begin())
            emit this->direction(DirectionUp); //up, if nothing down
        else
            emit this->direction(direction);// save inertia otherwise
    }
}

ButtonController::ButtonController(QObject* parent)
    : QObject(parent) {
}

void ButtonController::connectAll() {
    connect(this, &ButtonController::newButton, this, &ButtonController::idle);
    connect(this, &ButtonController::goIdle, this, &ButtonController::idle);
    connect(this, &ButtonController::arrived, this, &ButtonController::idle);
    connect(this, &ButtonController::direction, this, [this](Direction) { idle(); });
}
