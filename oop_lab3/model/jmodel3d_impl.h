#pragma once


namespace Jora {

class Model3DImpl {
public:
    virtual operator bool() const noexcept = 0;
    virtual bool isEmpty() const noexcept = 0;
    virtual bool isValid(size_t points_amount) = 0;
};

}