#pragma once
#include "jnode.h"
#include "jiterator.h"

namespace jora {
    template <typename Type>
    class List;

    template<typename Type>
    class ListIteratorBase : public Iterator {
    public:
        virtual operator bool() const noexcept override;
        virtual bool operator==(const ListIteratorBase& other) const;
        virtual bool operator!=(const ListIteratorBase& other) const;

    protected:
        ListIteratorBase() noexcept;
        ListIteratorBase(const ListIteratorBase& other) noexcept;
        explicit ListIteratorBase(const std::weak_ptr<Node<Type>>& ptr) noexcept;

        virtual std::shared_ptr<Node<Type>> node() const;
        virtual void setPtr(const std::weak_ptr<Node<Type>>& ptr) noexcept;

    private:
        std::weak_ptr<Node<Type>> _ptr;
    };

    template<typename Type>
    class ListIterator final : public ListIteratorBase<Type> {
    public:
        ListIterator() noexcept;
        ListIterator(const ListIterator<Type>& other) noexcept;

        virtual inline ListIterator& operator++();
        virtual inline ListIterator operator++(int);
        virtual Type& operator*() const;
        virtual Type* operator->() const;

    private:
        friend class List<Type>;
        virtual std::shared_ptr<Node<Type>> node() const override;
        explicit ListIterator(const std::weak_ptr<Node<Type>>& ptr) noexcept;
    };

    template<typename Type>
    class ConstListIterator final : public ListIteratorBase<Type> {
    public:
        ConstListIterator() noexcept;
        ConstListIterator(const ConstListIterator<Type>& other) noexcept;
        ConstListIterator(const ListIterator<Type>& other) noexcept;

        virtual ConstListIterator& operator++();
        virtual ConstListIterator operator++(int);
        virtual const Type& operator*() const;
        virtual const Type* operator->() const;

    private:
        friend class List<Type>;
        virtual std::shared_ptr<Node<Type>> node() const override;
        ConstListIterator(const std::weak_ptr<Node<Type>>& ptr) noexcept;
    };


    /********** IMPLEMENTATION **********/
    template<typename Type>
    inline ListIteratorBase<Type>::ListIteratorBase() noexcept
        : _ptr() {}
    template<typename Type>
    inline ListIteratorBase<Type>::ListIteratorBase(const ListIteratorBase& other) noexcept
        : _ptr(other._ptr) {}
    template<typename Type>
    inline ListIteratorBase<Type>::ListIteratorBase(const std::weak_ptr<Node<Type>>& ptr) noexcept
        : _ptr(ptr) {}

    template<typename Type>
    inline ListIteratorBase<Type>::operator bool() const noexcept {
        return !_ptr.expired();
    }
    template<typename Type>
    inline std::shared_ptr<Node<Type>> ListIteratorBase<Type>::node() const {
        std::shared_ptr<Node<Type>> locked = _ptr.lock();
        if (!locked)
            throw IteratorExpiredException(__FILE__, __FUNCTION__, __LINE__);
        return locked;
    }
    template<typename Type>
    inline bool ListIteratorBase<Type>::operator==(const ListIteratorBase& other) const {
        return _ptr.lock() == other._ptr.lock();
    }
    template<typename Type>
    inline bool ListIteratorBase<Type>::operator!=(const ListIteratorBase& other) const {
        return _ptr.lock() != other._ptr.lock();
    }
    template<typename Type>
    inline void ListIteratorBase<Type>::setPtr(const std::weak_ptr<Node<Type>>& ptr) noexcept {
        _ptr = ptr;
    }

    template<typename Type>
    inline ListIterator<Type>::ListIterator() noexcept
        : ListIteratorBase<Type>() {}
    template<typename Type>
    inline ListIterator<Type>::ListIterator(const ListIterator<Type>& other) noexcept
        : ListIteratorBase<Type>(other) {}
    template<typename Type>
    inline ListIterator<Type>::ListIterator(const std::weak_ptr<Node<Type>>& ptr) noexcept
        : ListIteratorBase<Type>(ptr) {}

    template<typename Type>
    inline ListIterator<Type>& ListIterator<Type>::operator++() {
        this->setPtr(this->node()->next());
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
        return this->node()->value();
    }
    template<typename Type>
    inline Type* ListIterator<Type>::operator->() const {
        return &this->node()->value();
    }
    template<typename Type>
    inline std::shared_ptr<Node<Type>> ListIterator<Type>::node() const {
        return ListIteratorBase<Type>::node();
    }

    template<typename Type>
    inline ConstListIterator<Type>::ConstListIterator() noexcept
        : ListIteratorBase<Type>() {}
    template<typename Type>
    inline ConstListIterator<Type>::ConstListIterator(const ConstListIterator<Type>& other) noexcept
        : ListIteratorBase<Type>(other) {}
    template<typename Type>
    inline ConstListIterator<Type>::ConstListIterator(const ListIterator<Type>& other) noexcept
        : ListIteratorBase<Type>(other) {}
    template<typename Type>
    inline ConstListIterator<Type>::ConstListIterator(const std::weak_ptr<Node<Type>>& ptr) noexcept
        : ListIteratorBase<Type>(ptr) {}

    template<typename Type>
    inline ConstListIterator<Type>& ConstListIterator<Type>::operator++() {
        this->setPtr(this->node()->next());
        return *this;
    }
    template<typename Type>
    inline ConstListIterator<Type> ConstListIterator<Type>::operator++(int) {
        ConstListIterator<Type> result(*this);
        ++(*this);
        return result;
    }
    template<typename Type>
    inline const Type& ConstListIterator<Type>::operator*() const {
        return this->node()->value();
    }
    template<typename Type>
    inline const Type* ConstListIterator<Type>::operator->() const {
        return &this->node()->value();
    }
    template<typename Type>
    inline std::shared_ptr<Node<Type>> ConstListIterator<Type>::node() const {
        return ListIteratorBase<Type>::node();
    }
}
