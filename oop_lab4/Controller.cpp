#include "Controller.h"

void ButtonController::idle() {
    _state = State::Idle;
}

void ButtonController::buttonPressed(int floor, bool isInside) {
    if (_state == State::WaitButton) {
        _state = State::ProcessingButton;
        if (floor == _savedFloor)
            emit waitForButton();
        else {
            _floorsToVisit.insert(floor);
            emit setDirection(floor > _savedFloor);
        }
    }
    else {
        _state = State::ProcessingButton;
        _floorsToVisit.insert(floor);
        emit buttonProcessed();
    }
}

void ButtonController::waitButton() {
    _state = State::WaitButton;
}

void ButtonController::requestDirection(int currentFloor, bool goUp) {
    _state = State::CheckDirection;
    if (_floorsToVisit.empty()) {
        _savedFloor = currentFloor;
        emit waitForButton();
    }
    else {
        std::set<int>::iterator it = _floorsToVisit.upper_bound(currentFloor); // got NEXT element
        if (it == _floorsToVisit.begin())
            emit setDirection(true); //up, if nothing down
        else if (it == _floorsToVisit.end())
            emit setDirection(false); // down, if nothing up
        else
            emit setDirection(goUp); // save inertia otherwise
    }
}

void ButtonController::requestArrival(int currentFloor) {
    _state = State::CheckArrival;
    auto it = _floorsToVisit.find(currentFloor);
    if (it == _floorsToVisit.end()) {
        emit goIdle();
    }
    else {
        _floorsToVisit.erase(it);
        emit arrived();
    }
}

ButtonController::ButtonController(QObject* parent)
    : QObject(parent) {
    connect(this, &ButtonController::buttonProcessed, this, &ButtonController::idle);
    connect(this, &ButtonController::goIdle, this, &ButtonController::idle);
    connect(this, &ButtonController::waitForButton, this, &ButtonController::waitButton);
    connect(this, &ButtonController::arrived, this, &ButtonController::idle);
    connect(this, &ButtonController::requestArrival, this, [this](int) { idle(); });
    connect(this, &ButtonController::requestDirection, this, [this](int) { idle(); });
}

