#pragma once
#include "jnode.h"
#include "jiterator.h"

namespace jora {
    template <typename Type>
    class List;

    template <typename Type>
    class ListIterator final : public Iterator {
    public:
        inline ListIterator() noexcept;
        inline ListIterator(const ListIterator<Type>& other) noexcept;
        inline ListIterator(ListIterator<Type>&& other) noexcept;

        virtual inline operator bool() const noexcept override;
        virtual inline ListIterator& operator++();
        virtual inline ListIterator operator++(int);
        virtual inline Type& operator*() const;
        virtual inline Type* operator->() const;

    private:
        friend class List<Type>;
        inline ListIterator(const std::weak_ptr<Node<Type>>& ptr) noexcept;
        inline ListIterator(const std::shared_ptr<Node<Type>>& ptr) noexcept;
        virtual inline std::shared_ptr<Node<Type>> node() const;

        std::weak_ptr<Node<Type>> _ptr;
    };


    /********** IMPLEMENTATION **********/
    template<typename Type>
    inline ListIterator<Type>::ListIterator() noexcept
        : _ptr() {}
    template<typename Type>
    inline ListIterator<Type>::ListIterator(const ListIterator<Type>& other) noexcept
        : _ptr(other._ptr) {}
    template<typename Type>
    inline ListIterator<Type>::ListIterator(ListIterator<Type>&& other) noexcept
        : _ptr(other._ptr) {};
    template<typename Type>
    inline ListIterator<Type>::ListIterator(const std::weak_ptr<Node<Type>>& ptr) noexcept
        : _ptr(ptr) {}
    template<typename Type>
    inline ListIterator<Type>::ListIterator(const std::shared_ptr<Node<Type>>& ptr) noexcept
        : _ptr(ptr) {}

    template<typename Type>
    inline ListIterator<Type>::operator bool() const noexcept {
        return !_ptr.expired();
    }
    template<typename Type>
    inline ListIterator<Type>& ListIterator<Type>::operator++() {
        _ptr = node()->next();
        return *this;
    }
    template<typename Type>
    inline ListIterator<Type> ListIterator<Type>::operator++(int) {
        ListIterator<Type> result(*this);
        ++(*this);
        return result;
    }
    template<typename Type>
    inline Type& ListIterator<Type>::operator*() const {
        return node()->value();
    }
    template<typename Type>
    inline Type* ListIterator<Type>::operator->() const {
        return &node()->value();
    }
    template<typename Type>
    inline std::shared_ptr<Node<Type>> ListIterator<Type>::node() const {
        std::shared_ptr<Node<Type>> locked = _ptr.lock();
        if (!locked)
            throw IteratorExpiredException(__FILE__, __FUNCTION__, __LINE__);
        return locked;
    }
}
