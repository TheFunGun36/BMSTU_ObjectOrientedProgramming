#pragma once
#include "jcontainer.h"
#include "jnode.h"
#include "jlistiterator.h"

namespace jora {
    template <typename Type>
    class List : public Container {
    public:
        using iterator = ListIterator<Type>;
        using const_iterator = ListIterator<const Type>;

        List() = default;
        explicit List(const List &other);
        List(List&& other);
        List(std::initializer_list<Type> init);
        List(Type *array, size_t length);
        List(std::list<Type>);
        ~List();

        List &operator=(std::initializer_list<Type> init);
        List &operator=(const List &other);
        List &operator=(List &&other) noexcept;
        List &operator=(std::list<Type> other);

        bool operator==(const List &other) const noexcept;
        bool operator!=(const List &other) const noexcept;

        operator bool() noexcept { return this->size(); }

        iterator begin();
        iterator end();
        const_iterator begin() const;
        const_iterator end() const;
        const_iterator cbegin() const;
        const_iterator cend() const;

        virtual void append(List &&other);
        virtual void append(const List &other);
        virtual void append(std::initializer_list<Type> values);
        virtual void append(Type &&value);
        virtual void append(const Type &value);

        virtual void replace(iterator element, Type &&value);
        virtual void replace(iterator begin, std::initializer_list<Type> values);
        virtual void replace(iterator begin, const List &other);

        virtual void insert(iterator before, Type &&value);
        virtual void insert(iterator before, const Type &value);
        virtual void insert(iterator before, const_iterator inputBegin, const_iterator inputEnd);
        virtual void insert(iterator before, std::initializer_list<Type> elements);

        virtual void remove(iterator element, size_t amount = 1);

        virtual void pushBack(Type &&value);
        virtual void pushBack(const Type &value);
        virtual void pushFront(Type &&value);
        virtual void pushFront(const Type &value);

        //virtual Type &&popBack();
        virtual Type &&popFront();
        virtual const Type &peekBack() const;
        virtual const Type &peekFront() const;

        virtual iterator find(const Type &value);
        virtual const_iterator find(const Type &value) const;

        virtual Type *toCArray();

        static iterator iteratorFromIndex(size_t index);
    private:
        std::shared_ptr<Node<Type>> _head = std::shared_ptr<Node<Type>>();
        std::weak_ptr<Node<Type>> _tail = std::weak_ptr<Node<Type>>();
    };
}
