#pragma once
#include <qobject.h>
#include <qtimer.h>

class Timer : public QObject {
    Q_OBJECT


signals:
    void tick();
    void timeout();

public slots:
    void set(int ticks);
    void reset();

private slots:
    void onTick();

public:
    enum class State {
        Idle,
        Set,
        Ticking,
    };

    Timer(int timerDelayMsec = 500, QObject* parent = nullptr);
    void connectAll();
    inline int ticks() const { return _ticks; }

private:
    State _state = State::Idle;
    QTimer _timer;
    int _ticks = 0;
    const int _timerDelayMsec;
};

