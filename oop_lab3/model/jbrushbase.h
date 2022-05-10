#pragma once
#include "pch.h"
#include "jcolorbase.h"

namespace Jora {

class BrushBase : public Printable {
public:
    virtual std::unique_ptr<BrushBase> copy() const = 0;

    inline virtual const ColorBase& color() const noexcept {
        return const_cast<BrushBase&>(*this).color();
    }
    virtual ColorBase& color() noexcept = 0;
    virtual void setColor(const ColorBase& color) noexcept = 0;

    inline virtual ~BrushBase() = default;

protected:
    BrushBase() = default;
    BrushBase(const BrushBase& other) = delete;
    BrushBase& operator=(const BrushBase& other) = delete;
};

}