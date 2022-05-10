#pragma once
#include "pch.h"
#include "jcolorbase.h"

namespace Jora {

class PenBase : public Printable {
public:
    virtual std::unique_ptr<PenBase> copy() const = 0;

    inline virtual const ColorBase& color() const noexcept {
        return const_cast<PenBase&>(*this).color();
    }
    virtual ColorBase& color() noexcept = 0;
    virtual void setColor(const ColorBase& color) noexcept = 0;

    inline virtual ~PenBase() = default;

protected:
    PenBase() = default;
    PenBase(const PenBase& other) = delete;
    PenBase& operator=(const PenBase& other) = delete;
};

}