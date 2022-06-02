#pragma once
#include <ostream>
#include "jreal.h"
#include "jprintable.h"
#include "property.h"

namespace Jora {

class Angle : public Printable {
public:
    Angle();
    Angle(const Angle& other) = default;

    static Angle fromDegrees(real value);
    static Angle fromRadians(real value);
    static real degreesFromRadians(real value);
    static real radiansFromDegrees(real value);
    static real optimizeDegrees(real value);
    static real optimizeRadians(real value);

    real degrees() const;
    real radians() const;
    void setDegrees(const real& value);
    void setRadians(const real& value);

    real cos() const;
    real sin() const;

    bool operator==(const Angle& other) const;
    bool operator!=(const Angle& other) const;

    Angle& operator=(const Angle& other);

    Angle& operator+=(const Angle& other);
    Angle& operator-=(const Angle& other);
    Angle& operator*=(real value);
    Angle& operator/=(real value);

    Angle operator+(const Angle& other) const;
    Angle operator-(const Angle& other) const;
    Angle operator*(real value) const;
    Angle operator/(real value) const;

protected:
    virtual std::ostream& addToStream(std::ostream& stream) const override;
    virtual std::wostream& addToStream(std::wostream& stream) const override;

private:
    real _radians;
    real _cos;
    real _sin;
};

}

