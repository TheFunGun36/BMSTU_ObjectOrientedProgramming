#pragma once
#include <qwidget.h>

class Button : public QObject {
    Q_OBJECT


signals:
    void pressed(int floor, bool isInside);
    void released(int floor, bool isInside);


public slots:
    void press();
    void release();


public:
    enum class State {
        Released,
        Pressed
    };

    Button(int floorIndex, bool isInside = false, QObject* parent = nullptr);

    inline State state() { return _state; }
    inline bool isInside() { return _isInside; }
    inline int floor() { return _floorIndex; }


private:
    State _state = State::Released;
    const bool _isInside;
    const int _floorIndex;
};

