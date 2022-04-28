#pragma once
#include <memory>
#include <list>
#include "jiteratorexception.h"

namespace jora {
    template <typename Type>
    class Iterator {
    public:
        virtual inline bool operator==(const Iterator &other) const {
            return !_ptr.owner_before(other._ptr) && !other._ptr.owner_before(_ptr);
        }
        virtual inline bool operator!=(const Iterator &other) const {
            return _ptr.owner_before(other._ptr) || other._ptr.owner_before(_ptr);
        }
        virtual inline operator bool() const noexcept {
            return _ptr.expired();
        }

    protected:
        Iterator() = default;

        virtual inline std::weak_ptr<Type> ptr() const { return _ptr; }
        virtual inline void setPtr(const std::weak_ptr<Type> &ptr) noexcept { _ptr = ptr; }
        virtual inline void setPtr(const std::shared_ptr<Type> &ptr) noexcept { _ptr = ptr; }
        virtual inline std::shared_ptr<Type> lock() const {
            if (_ptr.expired())
                throw IteratorExpiredException(__FILE__, __FUNCTION__, __LINE__);
            return _ptr.lock();
        }
        virtual inline bool atEnd() const {
            return !_ptr.lock();
        }

    private:
        std::weak_ptr<Type> _ptr = std::weak_ptr<Type>();
    };
}
