#pragma once

#include <QtWidgets/QMainWindow>
#include <qvector.h>
#include "ui_MainWindow.h"
#include "Cabin.h"
#include <qqueue.h>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = Q_NULLPTR);

private:
    Ui::MainWindowClass ui;
    Cabin _cabin;
    Button* _buttons[8];
    QQueue<int> wow;

    void buttonPressed(int index);
    void addToHistory(QString string);
    void setDarkTheme();
    void connectLogs();
    void connectLogsCabin();
    void connectLogsDoors();
    void connectLogsController();
    void connectLogsTimer();
    void connectButtons();
    void checkWow();

private slots:
    void update();

};
