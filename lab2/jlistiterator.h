#pragma once
#include "jnode.h"
#include "jiterator.h"

namespace jora {
    template <typename Type>
    class ListIterator : public Iterator<Node<Type>> {
    public:
        ListIterator() noexcept;
        ListIterator(const ListIterator<Type>& other) noexcept;
        ListIterator(const std::weak_ptr<Node<Type>>& ptr) noexcept;
        ListIterator(const std::shared_ptr<Node<Type>>& ptr) noexcept;

        virtual inline const Type* operator->() const;
        virtual inline Type* operator->();
        virtual inline const Type& operator*() const;
        virtual inline Type& operator*();
        virtual inline ListIterator<Type>& operator=(const ListIterator<Type>& other);
        virtual ListIterator<Type>& operator++();
        virtual ListIterator<Type> operator++(int);

        virtual inline std::shared_ptr<Node<Type>> node();
    };


    /********** IMPLEMENTATION **********/
    template<typename Type>
    inline ListIterator<Type>::ListIterator() noexcept
        : Iterator<Node<Type>>() {}
    template<typename Type>
    inline ListIterator<Type>::ListIterator(const ListIterator<Type>& other) noexcept
        : Iterator<Node<Type>>(other) {}
    template<typename Type>
    inline ListIterator<Type>::ListIterator(const std::weak_ptr<Node<Type>>& ptr) noexcept
        : Iterator<Node<Type>>(ptr) {}
    template<typename Type>
    inline ListIterator<Type>::ListIterator(const std::shared_ptr<Node<Type>>& ptr) noexcept
        : Iterator<Node<Type>>(ptr) {}

    template<typename Type>
    inline const Type* ListIterator<Type>::operator->() const {
        return &this->lock()->value();
    }
    template<typename Type>
    inline Type* ListIterator<Type>::operator->() {
        return &this->lock()->value();
    }
    template<typename Type>
    inline const Type& ListIterator<Type>::operator*() const {
        return this->lock()->value();
    }
    template<typename Type>
    inline Type& ListIterator<Type>::operator*() {
        return this->lock()->value();
    }
    template<typename Type>
    inline ListIterator<Type>& ListIterator<Type>::operator=(const ListIterator<Type>& other) {
        this->setPtr(other.ptr());
        return *this;
    }
    template<typename Type>
    inline ListIterator<Type>& ListIterator<Type>::operator++() {
        this->setPtr(this->lock()->next());
        return *this;
    }
    template<typename Type>
    inline ListIterator<Type> ListIterator<Type>::operator++(int) {
        ListIterator<Type> tmp(*this);
        this->setPtr(this->lock()->next());
        return tmp;
    }
    template<typename Type>
    inline std::shared_ptr<Node<Type>> ListIterator<Type>::node() {
        return this->lock();
    }
}
