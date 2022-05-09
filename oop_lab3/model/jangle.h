#pragma once
#include <ostream>
#include "jnumerical.h"

namespace Jora {

class Angle {
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

    friend std::ostream& operator<<(std::ostream& stream, const Angle& a);
    friend std::wostream& operator<<(std::wostream& stream, const Angle& a);

private:
    real _radians;
    real _cos;
    real _sin;
};

}

