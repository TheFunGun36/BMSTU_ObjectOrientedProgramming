#pragma once
#include <memory>
#include "jiteratorexception.h"

namespace jora {
    template <typename Type>
    class ConstIterator {
    public:
        virtual inline std::shared_ptr<const Type> operator->() {
            if (_ptr.expired())
                throw IteratorExpiredException(__FILE__, __FUNCTION__, __LINE__);
            return _ptr.lock();
        }

        virtual void operator++() = 0;
        virtual void operator++(int) = 0;

    private:
        std::weak_ptr<Type> _ptr = nullptr;
    };

    template <typename Type>
    class Iterator {

    };
}
