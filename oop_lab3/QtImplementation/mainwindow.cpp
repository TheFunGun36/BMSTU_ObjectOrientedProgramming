#include "mainwindow.h"
#include "../model/jinitializationmanager.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent) {
    ui.setupUi(this);

    using namespace Jora;
    InitializationManager im;
    modelViewer = im.createModelViewer();
}
