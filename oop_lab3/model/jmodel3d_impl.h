#pragma once


namespace Jora {

class Model3DImpl {
public:
    virtual operator bool() const noexcept = 0;
    virtual bool isValid() const noexcept = 0;
};

}