#pragma once
#include <memory>
#include <list>
#include "jiteratorexception.h"

namespace jora {
    template <typename Type>
    class Iterator {
    public:
        virtual void operator++() = 0;
        virtual void operator++(int) = 0;
        virtual inline bool operator==(const Iterator &other) {
            return _ptr == other._ptr;
        }
        virtual inline bool operator!=(const Iterator &other) {
            return _ptr != other._ptr;
        }

    protected:
        virtual inline std::weak_ptr<Type> ptr() { return _ptr; }
        virtual inline void setPtr(const std::weak_ptr<Type> &ptr) noexcept { _ptr = ptr; }
        virtual inline void setPtr(const std::shared_ptr<Type> &ptr) noexcept { _ptr = ptr; }
        virtual inline std::shared_ptr<Type> lock() {
            if (_ptr.expired())
                throw IteratorExpiredException(__FILE__, __FUNCTION__, __LINE__);
            return _ptr.lock();
        }

    private:
        std::weak_ptr<Type> _ptr = std::weak_ptr<Type>();
    };
}
