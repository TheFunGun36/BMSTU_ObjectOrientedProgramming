#pragma once
#include "jnode.h"
#include "jiterator.h"

namespace jora {
    template <typename Type>
    class ListIterator : public Iterator<Node<Type>> {
    public:
        virtual inline const Type* operator->() const {
            return &this->lock()->value();
        }
        virtual inline Type* operator->() {
            return &this->lock()->value();
        }
        virtual inline Type& operator*() {
            return this->lock()->value();
        }
        virtual inline const Type& operator*() const {
            return this->lock()->value();
        }

        virtual inline ListIterator& operator=(const ListIterator& other) {
            this->setPtr(other.ptr());
            return *this;
        }
        virtual ListIterator& operator++() {
            this->setPtr(this->lock()->next());
            return *this;
        }
        virtual ListIterator operator++(int) {
            ListIterator tmp(*this);
            this->setPtr(this->lock()->next());
            return tmp;
        }

        virtual inline std::shared_ptr<Node<Type>> node() {
            return this->lock();
        }
    };
}
