#pragma once
#include "jpenbase.h"
#include <qpen.h>

class Pen : public Jora::PenBase {
public:
    Pen() = default;
    Pen(const Pen& other) = default;
    Pen(const QPen& other) noexcept;

    Pen& operator=(const Pen& other) = default;
    inline Pen& operator=(const QPen& other) noexcept { _value = other; }

    inline operator QPen() { return _value; }

    virtual ~Pen() = default;

    virtual std::unique_ptr<PenBase> copy() const override;

    virtual std::unique_ptr<Jora::ColorBase> color() const noexcept override;
    virtual void setColor(const Jora::ColorBase& color) noexcept override;

private:
    QPen _value;
};
