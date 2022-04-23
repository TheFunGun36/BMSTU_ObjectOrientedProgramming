#pragma once
#include "jiterator.h"
#include "jnode.h"

namespace jora {
    template <typename Type>
    class ListIterator : public Iterator<Node<Type>> {
        virtual inline std::shared_ptr<const Type> operator->() {
            return this->lock()->value();
        }
        virtual inline std::shared_ptr<Type> operator->() const {
            return this->lock()->value();
        }
        virtual inline Type &operator*() {
            return *this->lock()->value();
        }
        virtual inline const Type &operator*() const {
            return *this->lock()->value();
        }

        virtual inline ListIterator &operator=(const ListIterator &other) {
            return this->setPtr(other.ptr());
        }
        virtual ListIterator &operator++() {
            return this->setPtr(this->lock()->next());
        }
        virtual ListIterator operator++(int) {
            ListIterator tmp(*this);
            this->setPtr(this->lock()->next());
            return tmp;
        }
    };
}
