#pragma once
#include "jviewfactorybase.h"

class QtFactory : public Jora::ViewFactoryBase {
public:
    virtual std::unique_ptr<Jora::PenBase> createPen() override;
    virtual std::unique_ptr<Jora::BrushBase> createBrush() override;
    virtual std::unique_ptr<Jora::PixmapBase> createPixmap() override;
    virtual std::unique_ptr<Jora::PainterBase> createPainter() override;
    virtual std::unique_ptr<Jora::WindowBase> createWindow() override;
};
