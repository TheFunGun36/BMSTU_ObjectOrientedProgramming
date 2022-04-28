#pragma once
#include <memory>
#include <list>
#include "jiteratorexception.h"

namespace jora {
    template <typename Type>
    class Iterator {
    public:
        virtual inline bool operator==(const Iterator& other) const;
        virtual inline bool operator!=(const Iterator& other) const;
        virtual inline operator bool() const noexcept;

    protected:
        Iterator() = default;

        virtual inline std::weak_ptr<Type> ptr() const;
        virtual inline void setPtr(const std::weak_ptr<Type>& ptr) noexcept;
        virtual inline std::shared_ptr<Type> lock() const;
        virtual inline bool atEnd() const;

    private:
        std::weak_ptr<Type> _ptr = std::weak_ptr<Type>();
    };


    /********** IMPLEMENTATION **********/
    template<typename Type>
    inline bool Iterator<Type>::operator==(const Iterator& other) const {
        return !_ptr.owner_before(other._ptr) && !other._ptr.owner_before(_ptr);
    }
    template<typename Type>
    inline bool Iterator<Type>::operator!=(const Iterator& other) const {
        return _ptr.owner_before(other._ptr) || other._ptr.owner_before(_ptr);
    }
    template<typename Type>
    inline Iterator<Type>::operator bool() const noexcept {
        return _ptr.expired();
    }
    template<typename Type>
    inline std::weak_ptr<Type> Iterator<Type>::ptr() const {
        return _ptr;
    }
    template<typename Type>
    inline void Iterator<Type>::setPtr(const std::weak_ptr<Type>& ptr) noexcept {
        _ptr = ptr;
    }
    template<typename Type>
    inline std::shared_ptr<Type> Iterator<Type>::lock() const {
        if (_ptr.expired())
            throw IteratorExpiredException(__FILE__, __FUNCTION__, __LINE__);
        return _ptr.lock();
    }
    template<typename Type>
    inline bool Iterator<Type>::atEnd() const {
        return !_ptr.lock();
    }
}
