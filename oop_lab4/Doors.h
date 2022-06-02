#pragma once
#include <qobject.h>
#include <qtimer.h>

class Doors : public QObject {
    Q_OBJECT


signals:
    void opened();
    void closed();
    void failToOpen();
    void failToClose();
    void opening();
    void closing();


public slots:
    void open();
    void close();
    void idle();

public:
    enum State {
        StateIdle,
        StateOpening,
        StateClosing
    };
    Q_ENUM(State);

    Doors(QObject* parent = nullptr);

    inline State state() { return _state; }

    inline void blockOpen() { _blockedForOpen = true; }
    inline void blockClose() { _blockedForClose = true; }
    inline void unblockOpen() { _blockedForOpen = false; }
    inline void unblockClose() { _blockedForClose = false; }

    inline int distance() { return _doorsDistance; }

private:
    State _state = StateIdle;

    int _doorsDistanceMin = 0;
    int _doorsDistanceMax = 5;
    int _doorsDistance = 5;

    bool _blockedForOpen = false;
    bool _blockedForClose = false;
    int _timerDelayMsec = 500;

    QTimer _timer;

    inline bool isOpen() { return _doorsDistance >= _doorsDistanceMax; }
    inline bool isClosed() { return _doorsDistance <= _doorsDistanceMin; }
};

