#pragma once
#include "jcolorbase.h"

namespace Jora {

class PenBase : public Printable {
public:
    virtual std::unique_ptr<PenBase> copy() const = 0;

    virtual std::unique_ptr<Jora::ColorBase> color() const noexcept = 0;
    virtual void setColor(const ColorBase& color) noexcept = 0;

    inline virtual ~PenBase() = default;

protected:
    PenBase() = default;
    PenBase(const PenBase& other) = delete;
    PenBase& operator=(const PenBase& other) = delete;
};

}