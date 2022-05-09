#pragma once
#include <ostream>
#include "jreal.h"
#include "jprintable.h"

namespace Jora {

class Angle : public Printable {
public:
    Angle() = default;
    Angle(const Angle& other) = default;

    static Angle fromDegrees(real value);
    static Angle fromRadians(real value);
    static real degreesFromRadians(real value);
    static real radiansFromDegrees(real value);
    static real optimizeDegrees(real value);
    static real optimizeRadians(real value);

    real degrees() const;
    real radians() const;
    void setDegrees(real value);
    void setRadians(real value);

    real cos() const;
    real sin() const;

    bool operator==(const Angle& other) const;
    bool operator!=(const Angle& other) const;

protected:
    virtual std::ostream& addToStream(std::ostream& stream) const override;
    virtual std::wostream& addToStream(std::wostream& stream) const override;

private:
    real _radians;
    real _cos;
    real _sin;
};

}

