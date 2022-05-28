#include "mainwindow.h"
#include "../model/jsolution.h"
#include "../model/jinitializationmanager.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent) {
    ui.setupUi(this);

    using namespace Jora;
    Solution solution;
    InitializationManager im(std::make_unique<Solution>(solution));
    modelViewer = im.createModelViewer();
}
