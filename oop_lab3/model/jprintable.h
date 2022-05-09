#pragma once
#include <string>
#include <ostream>

namespace Jora {

class Printable {
public:
    virtual std::string toString() const final;
    virtual std::wstring toWString() const final;
    friend std::ostream& operator<<(std::ostream& stream, const Printable& position);
    friend std::wostream& operator<<(std::wostream& stream, const Printable& position);

    inline virtual ~Printable() = default;

protected:
    virtual std::ostream& addToStream(std::ostream& stream) const = 0;
    virtual std::wostream& addToStream(std::wostream& stream) const = 0;
};

}

