#pragma once
#include <memory>
#include <list>
#include "jiteratorexception.h"

namespace jora {
    class Iterator {
    public:
        virtual operator bool() const noexcept = 0;
    };
}
