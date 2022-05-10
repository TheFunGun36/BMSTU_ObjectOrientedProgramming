#pragma once
#include "pch.h"
#include "jpenbase.h"
#include "jbrushbase.h"

namespace Jora {

class PainterBase : public Printable {
public:
    virtual std::unique_ptr<PainterBase> copy() const = 0;

    virtual inline const PenBase& pen() const { return *_pen; }
    virtual inline PenBase& pen() { return *_pen; }
    virtual inline void setPen(const PenBase& pen) { _pen = pen.copy(); }

    virtual inline const BrushBase& brush() const { return *_brush; }
    virtual inline BrushBase& brush() { return *_brush; }
    virtual inline void setBrush(const BrushBase& brush) { _brush = brush.copy(); }

    virtual ~PainterBase() = default;

protected:
    PainterBase() = delete;
    PainterBase(const PainterBase& other) = delete;
    PainterBase& operator=(const PainterBase& other) = delete;

    inline PainterBase(const PenBase& pen, const BrushBase& brush)
        : _pen(pen.copy()), _brush(brush.copy()) {
    }

    std::unique_ptr<PenBase> _pen;
    std::unique_ptr<BrushBase> _brush;
};

}