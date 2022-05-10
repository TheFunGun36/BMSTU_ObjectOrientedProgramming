#include "factory.h"
#include "pen.h"
#include "brush.h"
#include "pixmap.h"
#include "painter.h"
#include "window.h"

using std::make_unique, std::unique_ptr;
using namespace Jora;

unique_ptr<PenBase> QtFactory::createPen() {
    return make_unique<Pen>();
}
unique_ptr<BrushBase> QtFactory::createBrush() {
    return make_unique<Brush>();
}
unique_ptr<PixmapBase> QtFactory::createPixmap() {
    return make_unique<Pixmap>();
}
unique_ptr<PainterBase> QtFactory::createPainter() {
    return make_unique<Painter>();
}
unique_ptr<WindowBase> QtFactory::createWindow() {
    return make_unique<Window>();
}

