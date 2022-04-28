#pragma once
#include <ostream>
#include "jcontainer.h"
#include "jnode.h"
#include "jlistiterator.h"
#include "jlistexception.h"

namespace jora {
    template <typename Type>
    class List : public Container {
    public:
        using iterator = ListIterator<Type>;
        using const_iterator = ListIterator<const Type>;

        List() = default;
        inline List(List&& other) noexcept;
        inline explicit List(const List& other);
        inline List(std::initializer_list<Type> initList);
        inline List(std::list<Type>& stdList);
        inline List(const Type* cArray, size_t length);
        inline List(const const_iterator& begin, const const_iterator& end);
        ~List() = default;

        inline List& operator=(List&& other) noexcept;
        inline List& operator=(const List& other);
        inline List& operator=(std::initializer_list<Type> initList);
        inline List& operator=(const std::list<Type>& stdList);

        inline List& operator+=(List&& other) noexcept;
        inline List& operator+=(const List& other);
        inline List& operator+=(std::initializer_list<Type> initList);
        inline List& operator+=(const std::list<Type>& stdList);
        inline List& operator+=(Type&& value);
        inline List& operator+=(const Type& value);

        inline List&& operator+(List&& other) const noexcept;
        inline List&& operator+(const List& other) const;
        inline List&& operator+(const std::initializer_list<Type>& stdList) const;
        inline List&& operator+(Type&& value) const;
        inline List&& operator+(const Type& value) const;

        friend std::ostream& operator<<(std::ostream& stream, const List& list);

        inline bool operator==(const List& other) const noexcept;
        inline bool operator!=(const List& other) const noexcept;

        inline iterator begin();
        inline iterator end();
        inline const_iterator begin() const;
        inline const_iterator end() const;
        inline const_iterator cbegin() const;
        inline const_iterator cend() const;

        inline List& append(List&& other) noexcept;
        inline List& append(const List& other);
        inline List& append(std::initializer_list<Type> initList);
        inline List& append(const std::list<Type>& stdList);
        inline List& append(const const_iterator& begin, const const_iterator& end);
        inline List& append(Type&& value);
        inline List& append(const Type& value);
        inline List& append(const Type* cArray, size_t length);

        inline List& insertAfter(iterator element, List&& other);
        inline List& insertAfter(iterator element, const List& other);
        inline List& insertAfter(iterator element, std::initializer_list<Type> initList);
        inline List& insertAfter(iterator element, const std::list<Type>& stdList);
        inline List& insertAfter(iterator element, const const_iterator& begin, const const_iterator& end);
        inline List& insertAfter(iterator element, Type&& value);
        inline List& insertAfter(iterator element, const Type& value);
        inline List& insertAfter(iterator element, const Type* cArray, size_t length);

        virtual size_t remove(iterator element, size_t amount = 1) noexcept;
        virtual size_t cutAfter(iterator element) noexcept;

        virtual bool pushBack(Type&& value) noexcept;
        virtual bool pushBack(const Type& value) noexcept;
        virtual bool pushFront(Type&& value) noexcept;
        virtual bool pushFront(const Type& value) noexcept;
        virtual Type&& popFront();
        virtual const Type& peekBack() const;
        virtual const Type& peekFront() const;

        virtual iterator find(const Type& value);
        virtual const_iterator find(const Type& value) const;

        virtual Type* toCArray() noexcept;

        virtual const_iterator iteratorFromIndex(size_t index) const;
        virtual iterator iteratorFromIndex(size_t index);

        virtual void clear() override;

    protected:
        virtual inline std::shared_ptr<Node<Type>> tail();
        virtual inline std::shared_ptr<const Node<Type>> tail() const;

    private:
        std::shared_ptr<Node<Type>> _head = std::shared_ptr<Node<Type>>();
        std::weak_ptr<Node<Type>> _tail = std::weak_ptr<Node<Type>>();
    };

    template<typename Type>
    inline List<Type>::List(List&& other) {
        _head = other._head;
        _tail = other._tail;
    }

    template<typename Type>
    inline List<Type>::List(const List<Type>& other) {
        append(other.begin(), other.end());
    }

    template<typename Type>
    inline List<Type>::List(std::initializer_list<Type> initList) {
        append(initList.begin(), initList.size());
    }

    template<typename Type>
    inline List<Type>::List(std::list<Type>& stdList) {
        append(stdList);
    }

    template<typename Type>
    inline List<Type>::List(const Type* cArray, size_t length) {
        append(cArray, length);
    }

    template<typename Type>
    inline List<Type>::List(const const_iterator& begin, const const_iterator& end) {
        append(begin, end);
    }

    template<typename Type>
    inline List<Type>& List<Type>::append(List<Type>&& other) {
        if (_head) {
            auto tail = _tail.lock();
            tail->setNext(other._head);
            _tail = other._tail;
        }
        else {
            _head = other._head;
            _tail = other._tail;
        }

        setSize(size() + other.size());

        return *this;
    }

    template<typename Type>
    inline List<Type>& List<Type>::append(const List<Type>& other) {
        return append(other.begin(), other.end());
    }

    template<typename Type>
    inline List<Type>& List<Type>::append(std::initializer_list<Type> initList) {
        return append(initList.begin(), initList.size());
    }

    template<typename Type>
    inline List<Type>& List<Type>::append(const std::list<Type>& stdList) {
        for (const auto& el : stdList)
            append(el);

        return *this;
    }

    template<typename Type>
    inline List<Type>& List<Type>::append(const const_iterator& begin, const const_iterator& end) {
        for (const_iterator it = begin; it != end; it++)
            append(*it);

        return *this;
    }

    template<typename Type>
    inline List<Type>& List<Type>::append(Type&& value) {
        return append(value);
    }

    template<typename Type>
    inline List<Type>& List<Type>::append(const Type& value) {
        try {
            if (!_head) {
                _head = Node<Type>::create(value);
                _tail = _head;
            }
            else {
                auto tail = _tail.lock();
                tail->setNext(Node<Type>::create(value));
                _tail = tail->next();
            }

            setSize(size() + 1);
        }
        catch (const NodeBadAllocException& e) {
            throw ListBadAllocException(__FILE__, __FUNCTION__, __LINE__);
        }

        return *this;
    }

    template<typename Type>
    inline List<Type>& List<Type>::append(const Type* cArray, size_t length) {
        if (!cArray)
            throw ListCArrayNullptrException(__FILE__, __FUNCTION__, __LINE__);

        for (const Type* ptr = cArray; ptr < cArray + length; ptr++)
            append(*ptr);

        return *this;
    }

    template<typename Type>
    inline List<Type>& List<Type>::operator=(List<Type>&& other) {
        _head = other._head;
        _tail = other._tail;
        setSize(other.size());
        return *this;
    }

    template<typename Type>
    inline List<Type>& List<Type>::operator=(const List<Type>& other) {
        _head = nullptr;
        return append(other);
    }
    
    template<typename Type>
    inline List<Type>& List<Type>::operator=(std::initializer_list<Type> initList) {
        _head = nullptr;
        return append(initList);
    }

    template<typename Type>
    inline List<Type>& List<Type>::operator=(const std::list<Type>& stdList) {
        _head = nullptr;
        return append(stdList);
    }

    template<typename Type>
    inline List<Type>& List<Type>::operator+=(List<Type>&& other) {
        return append(std::move(other));
    }

    template<typename Type>
    inline List<Type>& List<Type>::operator+=(const List<Type>& other) {
        return append(other);
    }

    template<typename Type>
    inline List<Type>& List<Type>::operator+=(std::initializer_list<Type> initList) {
        return append(initList);
    }

    template<typename Type>
    inline List<Type>& List<Type>::operator+=(const std::list<Type>& stdList) {
        return append(stdList);
    }

    template<typename Type>
    inline List<Type>& List<Type>::operator+=(Type&& value) {
        return append(std::move(value));
    }

    template<typename Type>
    inline List<Type>& List<Type>::operator+=(const Type& value) {
        return append(value);
    }

    template<typename Type>
    inline List<Type>&& List<Type>::operator+(List<Type>&& other) const {
        List<Type> copy(*this);
        copy.append(std::move(other));
        return std::move(copy);
    }

    template<typename Type>
    inline List<Type>&& List<Type>::operator+(const List<Type>& other) const {
        List<Type> copy(*this);
        copy.append(other);
        return std::move(copy);
    }

    template<typename Type>
    inline List<Type>&& List<Type>::operator+(const std::initializer_list<Type>& stdList) const {
        List<Type> copy(*this);
        copy.append(stdList);
        return std::move(copy);
    }

    template<typename Type>
    inline List<Type>&& List<Type>::operator+(Type&& value) const {
        List<Type> copy(*this);
        copy.append(std::move(value));
        return std::move(copy);
    }

    template<typename Type>
    inline List<Type>&& List<Type>::operator+(const Type& value) const {
        List<Type> copy(*this);
        copy.append(value);
        return std::move(copy);
    }

    template<typename Type>
    std::ostream& operator<<(std::ostream& stream, const List<Type>& list) {
        return stream << "[list, size " << list->size() << "]";
    }
    
    template<typename Type>
    inline bool List<Type>::operator==(const List& other) const noexcept {
        if (size() != other.size())
            return false;

        const_iterator it1 = begin();
        const_iterator it2 = other.begin();
        bool eq = true;

        while (eq && it1 != end())
            eq = *it1++ == *it2++;

        return eq;
    }

    template<typename Type>
    inline bool List<Type>::operator!=(const List& other) const noexcept {
        return !(*this == other);
    }

    template <typename Type>
    inline List<Type>& List<Type>::insertAfter(ListIterator<Type> element, List&& other) {
        if (other.size()) {
            std::shared_ptr<Node<Type>> node = element.node();
            std::shared_ptr<Node<Type>> otherTail = other.tail();
            std::shared_ptr<Node<Type>> saved_next = node->next();

            node->setNext(other._head);
            otherTail->setNext(saved_next);
            setSize(size() + other.size());
        }
        return *this;
    }

    template <typename Type>
    inline List<Type>& List<Type>::insertAfter(ListIterator<Type> element, const List& other) {
        for (const Type& el : other)
            insertAfter(element++, el);
        return *this;
    }

    template <typename Type>
    inline List<Type>& List<Type>::insertAfter(ListIterator<Type> element, std::initializer_list<Type> initList) {
        for (const Type& el : initList)
            insertAfter(element++, el);
        return *this;
    }

    template <typename Type>
    inline List<Type>& List<Type>::insertAfter(ListIterator<Type> element, const std::list<Type>& stdList) {
        for (const Type& el : stdList)
            insertAfter(element++, el);
        return *this;
    }

    template <typename Type>
    inline List<Type>& List<Type>::insertAfter(ListIterator<Type> element, const const_iterator& begin, const const_iterator& end) {
        for (auto it = begin; it != end; it++)
            insertAfter(element++, *it);
        return *this;
    }

    template <typename Type>
    inline List<Type>& List<Type>::insertAfter(ListIterator<Type> element, Type&& value) {
        return insertAfter(element, value);
    }

    template <typename Type>
    inline List<Type>& List<Type>::insertAfter(iterator element, const Type& value) {
        std::shared_ptr<Node<Type>> nodeCur = element.node();
        std::shared_ptr<Node<Type>> nodeNew = Node<Type>::create(value, nodeCur->next());
        nodeCur->setNext(nodeNew);
        setSize(size() + 1);
        return *this;
    }

    template <typename Type>
    inline List<Type>& List<Type>::insertAfter(iterator element, const Type* cArray, size_t length) {
        if (!cArray)
            throw ListCArrayNullptrException(__FILE__, __FUNCTION__, __LINE__);

        for (int i = 0; i < length; i++)
            insertAfter(element++, cArray[i]);
        return *this;
    }

    template <typename Type>
    inline void List<Type>::clear() {
        _head = nullptr;
        _tail = _head;
        setSize(0);
    }

    template <typename Type>
    inline size_t List<Type>::remove(iterator element, size_t amount) noexcept {
        size_t count = 0;
        std::shared_ptr<Node<Type>> node = element.node();

        while (amount && element) {
            count++;
            element++;
            amount--;
        }

        if (element)
            node->setNext(element.node());
        setSize(size() - count);
        return count;
    }

    template <typename Type>
    inline size_t List<Type>::cutAfter(iterator element) noexcept {
        return remove(element, size());
    }

    template <typename Type>
    inline bool List<Type>::pushBack(Type&& value) noexcept {
        return pushBack(value);
    }

    template <typename Type>
    inline bool List<Type>::pushBack(const Type& value) noexcept {
        bool result = true;
        try {
            append(value);
        }
        catch (const ListException& e) {
            result = false;
        }

        return result;
    }

    template <typename Type>
    inline bool List<Type>::pushFront(Type&& value) noexcept {
    }

    template <typename Type>
    inline bool List<Type>::pushFront(const Type& value) noexcept {
        bool result = true;
        try {
            _head = Node<Type>::create(value, _head);
        }
        catch (const NodeException& e) {
            result = false;
        }

        return result;
    }

    template <typename Type>
    inline Type&& List<Type>::popFront() {
        if (!_head)
            throw ListEmptyException(__FILE__, __FUNCTION__, __LINE__);

        Type value = std::move(_head->value());
        _head = _head->next();
        return std::move(value);
    }

    template <typename Type>
    inline const Type& List<Type>::peekBack() const {
        return tail()->value();
    }

    template <typename Type>
    inline const Type& List<Type>::peekFront() const {
        if (!_head)
            throw ListEmptyException(__FILE__, __FUNCTION__, __LINE__);

        return _head->value();
    }
}
