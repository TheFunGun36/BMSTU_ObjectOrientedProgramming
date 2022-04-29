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

        List() noexcept;
        inline List(List<Type>&& other) noexcept;
        inline explicit List(const List<Type>& other);
        inline List(std::initializer_list<Type> initList);
        inline explicit List(std::list<Type>& stdList);
        inline explicit List(const Type* cArray, size_t length);
        inline explicit List(ListIterator<const Type> begin, ListIterator<const Type> end);
        inline explicit List(size_t count, const Type& value = 13);
        inline explicit List(size_t count, Type&& value);
        ~List() = default;

        inline List<Type>& operator=(List<Type>&& other) noexcept;
        inline List<Type>& operator=(const List<Type>& other);
        inline List<Type>& operator=(std::initializer_list<Type> initList);
        inline List<Type>& operator=(const std::list<Type>& stdList);

        inline List<Type>& operator+=(List<Type>&& other) noexcept;
        inline List<Type>& operator+=(const List<Type>& other);
        inline List<Type>& operator+=(std::initializer_list<Type> initList);
        inline List<Type>& operator+=(const std::list<Type>& stdList);
        inline List<Type>& operator+=(Type&& value);
        inline List<Type>& operator+=(const Type& value);

        inline List<Type>&& operator+(List<Type>&& other) const;
        inline List<Type>&& operator+(const List<Type>& other) const;
        inline List<Type>&& operator+(const std::initializer_list<Type>& stdList) const;
        inline List<Type>&& operator+(Type&& value) const;
        inline List<Type>&& operator+(const Type& value) const;

        inline bool operator==(const List<Type>& other) const noexcept;
        inline bool operator!=(const List<Type>& other) const noexcept;

        inline ListIterator<Type> begin();
        inline ListIterator<Type> end();
        inline ListIterator<const Type> begin() const;
        inline ListIterator<const Type> end() const;
        inline ListIterator<const Type> cbegin() const;
        inline ListIterator<const Type> cend() const;

        inline ListIterator<Type> last();
        inline ListIterator<const Type> last() const;
        inline Type& front();
        inline const Type& front() const;
        inline Type& back();
        inline const Type& back() const;

        inline List<Type>& append(List<Type>&& other) noexcept;
        inline List<Type>& append(const List<Type>& other);
        inline List<Type>& append(std::initializer_list<Type> initList);
        inline List<Type>& append(const std::list<Type>& stdList);
        inline List<Type>& append(ListIterator<const Type> begin, ListIterator<const Type> end);
        inline List<Type>& append(Type&& value);
        inline List<Type>& append(const Type& value);
        inline List<Type>& append(const Type* cArray, size_t length);

        inline List<Type>& insertAfter(ListIterator<Type> element, List<Type>&& other);
        inline List<Type>& insertAfter(ListIterator<Type> element, const List<Type>& other);
        inline List<Type>& insertAfter(ListIterator<Type> element, std::initializer_list<Type> initList);
        inline List<Type>& insertAfter(ListIterator<Type> element, const std::list<Type>& stdList);
        inline List<Type>& insertAfter(ListIterator<Type> element, ListIterator<const Type> begin, ListIterator<const Type> end);
        inline List<Type>& insertAfter(ListIterator<Type> element, Type&& value);
        inline List<Type>& insertAfter(ListIterator<Type> element, const Type& value);
        inline List<Type>& insertAfter(ListIterator<Type> element, const Type* cArray, size_t length);

        virtual size_t remove(ListIterator<Type> element, size_t amount = 1) noexcept;
        virtual size_t cutAfter(ListIterator<Type> element) noexcept;

        virtual bool pushBack(Type&& value) noexcept;
        virtual bool pushBack(const Type& value) noexcept;
        virtual bool pushFront(Type&& value) noexcept;
        virtual bool pushFront(const Type& value) noexcept;
        virtual Type&& popFront();
        virtual const Type& peekBack() const;
        virtual const Type& peekFront() const;

        virtual ListIterator<Type> find(const Type& value);
        virtual ListIterator<const Type> find(const Type& value) const;

        virtual Type* toCArray() noexcept;

        virtual ListIterator<const Type> iteratorFromIndex(size_t index) const;
        virtual ListIterator<Type> iteratorFromIndex(size_t index);

        virtual void clear() override;

    protected:
        virtual inline std::shared_ptr<Node<Type>> tail();
        virtual inline std::shared_ptr<const Node<Type>> tail() const;

    private:
        std::shared_ptr<Node<Type>> _head = std::shared_ptr<Node<Type>>();
        std::weak_ptr<Node<Type>> _tail = std::weak_ptr<Node<Type>>();
    };


    /********** IMPLEMENTATION **********/
    template<typename Type>
    inline List<Type>::List() noexcept {
        _head = nullptr;
        _tail = _head;
    }
    template<typename Type>
    inline List<Type>::List(List<Type>&& other) noexcept
        : List() {
        _head = other._head;
        _tail = other._tail;
    }
    template<typename Type>
    inline List<Type>::List(const List<Type>& other)
        : List() {
        append(other.begin(), other.end());
    }
    template<typename Type>
    inline List<Type>::List(std::initializer_list<Type> initList)
        : List() {
        append(initList.begin(), initList.size());
    }
    template<typename Type>
    inline List<Type>::List(std::list<Type>& stdList)
        : List() {
        append(stdList);
    }
    template<typename Type>
    inline List<Type>::List(const Type* cArray, size_t length)
        : List() {
        append(cArray, length);
    }
    template<typename Type>
    inline List<Type>::List(ListIterator<const Type> begin, ListIterator<const Type> end)
        : List() {
        append(begin, end);
    }
    template<typename Type>
    inline List<Type>::List(size_t count, const Type& value)
        : List() {
        for (int i = 0; i < count; i++)
            append(value);
    }
    template<typename Type>
    inline List<Type>::List(size_t count, Type&& value)
        : List(count, value) {}

    template<typename Type>
    inline List<Type>& List<Type>::append(List<Type>&& other) noexcept {
        if (!other)
            return *this;

        std::shared_ptr<Node<Type>> tail = _tail.lock();
        if (tail) {
            tail->setNext(other._head);
            _tail = other._tail;
            setSize(size() + other.size());
        }
        else {
            _head = other._head;
            _tail = other._tail;
            setSize(other.size());
        }
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
    inline List<Type>& List<Type>::append(ListIterator<const Type> begin, ListIterator<const Type> end) {
        while (begin != end)
            append(*begin++);
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
        catch (const NodeBadAllocException&) {
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
        for (const Type& el : other) {
            insertAfter(element, el);
            ++element;
        }
        return *this;
    }
    template <typename Type>
    inline List<Type>& List<Type>::insertAfter(ListIterator<Type> element, std::initializer_list<Type> initList) {
        for (const Type& el : initList) {
            insertAfter(element, el);
            ++element;
        }
        return *this;
    }
    template <typename Type>
    inline List<Type>& List<Type>::insertAfter(ListIterator<Type> element, const std::list<Type>& stdList) {
        for (const Type& el : stdList) {
            insertAfter(element, el);
            ++element;
        }
        return *this;
    }
    template <typename Type>
    inline List<Type>& List<Type>::insertAfter(ListIterator<Type> element, ListIterator<const Type> begin, ListIterator<const Type> end) {
        for (auto it = begin; it != end; it++) {
            insertAfter(element, *it);
            ++element;
        }
        return *this;
    }
    template <typename Type>
    inline List<Type>& List<Type>::insertAfter(ListIterator<Type> element, Type&& value) {
        return insertAfter(element, value);
    }
    template <typename Type>
    inline List<Type>& List<Type>::insertAfter(ListIterator<Type> element, const Type& value) {
        std::shared_ptr<Node<Type>> nodeCur = element.node();
        std::shared_ptr<Node<Type>> nodeNew = Node<Type>::create(value, nodeCur->next());
        nodeCur->setNext(nodeNew);
        setSize(size() + 1);
        return *this;
    }
    template <typename Type>
    inline List<Type>& List<Type>::insertAfter(ListIterator<Type> element, const Type* cArray, size_t length) {
        if (!cArray)
            throw ListCArrayNullptrException(__FILE__, __FUNCTION__, __LINE__);
        for (int i = 0; i < length; i++)
            insertAfter(element++, cArray[i]);
        return *this;
    }
    
    template<typename Type>
    inline List<Type>& List<Type>::operator=(List<Type>&& other) noexcept {
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
    inline List<Type>& List<Type>::operator+=(List<Type>&& other) noexcept {
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
    inline bool List<Type>::operator==(const List<Type>& other) const noexcept {
        if (size() != other.size())
            return false;
        ListIterator<const Type> it1 = begin();
        ListIterator<const Type> it2 = other.begin();
        bool eq = true;
        while (eq && it1 != end())
            eq = *it1++ == *it2++;
        return eq;
    }
    template<typename Type>
    inline bool List<Type>::operator!=(const List& other) const noexcept {
        return !(*this == other);
    }
    
    template<typename Type>
    inline ListIterator<Type> List<Type>::begin() {
        return ListIterator<Type>(_head);
    }
    template<typename Type>
    inline ListIterator<Type> List<Type>::end() {
        return ListIterator<Type>();
    }
    template<typename Type>
    inline ListIterator<const Type> List<Type>::begin() const {
        return cbegin();
    }
    template<typename Type>
    inline ListIterator<const Type> List<Type>::end() const {
        return cend();
    }
    template<typename Type>
    inline ListIterator<const Type> List<Type>::cbegin() const {
        return ListIterator<const Type>(_head);
    }
    template<typename Type>
    inline ListIterator<const Type> List<Type>::cend() const {
        return ListIterator<const Type>();
    }

    template<typename Type>
    inline ListIterator<Type> List<Type>::last() {
        return ListIterator<Type>(tail());
    }

    template<typename Type>
    inline ListIterator<const Type> List<Type>::last() const {
        return ListIterator<const Type>(tail());
    }

    template<typename Type>
    inline Type& List<Type>::front() {
        if (!_head)
            throw ListEmptyException(__FILE__, __FUNCTION__, __LINE__);
        return _head->value();
    }

    template<typename Type>
    inline const Type& List<Type>::front() const {
        if (!_head)
            throw ListEmptyException(__FILE__, __FUNCTION__, __LINE__);
        return _head->value();
    }

    template<typename Type>
    inline Type& List<Type>::back() {
        return tail()->value();
    }

    template<typename Type>
    inline const Type& List<Type>::back() const {
        return tail()->value();
    }
    
    template <typename Type>
    inline void List<Type>::clear() {
        _head = nullptr;
        _tail = _head;
        setSize(0);
    }
    
    template<typename Type>
    inline std::shared_ptr<Node<Type>> List<Type>::tail() {
        if (_tail.expired())
            throw ListEmptyException(__FILE__, __FUNCTION__, __LINE__);
        return _tail.lock();
    }
    template<typename Type>
    inline std::shared_ptr<const Node<Type>> List<Type>::tail() const {
        if (_tail.expired())
            throw ListEmptyException(__FILE__, __FUNCTION__, __LINE__);
        return _tail.lock();
    }
    
    template <typename Type>
    inline size_t List<Type>::remove(ListIterator<Type> element, size_t amount) noexcept {
        size_t count = 0;
        std::shared_ptr<Node<Type>> node = element.node();
        while (amount && element) {
            ++count;
            ++element;
            --amount;
        }
        if (element)
            node->setNext(element.node());
        setSize(size() - count);
        return count;
    }
    template <typename Type>
    inline size_t List<Type>::cutAfter(ListIterator<Type> element) noexcept {
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
        catch (const ListException&) {
            result = false;
        }
        return result;
    }
    template <typename Type>
    inline bool List<Type>::pushFront(Type&& value) noexcept {
        return pushFront(value);
    }
    template <typename Type>
    inline bool List<Type>::pushFront(const Type& value) noexcept {
        bool result = true;
        try {
            _head = Node<Type>::create(value, _head);
        }
        catch (const NodeException&) {
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
    
    template<typename Type>
    inline ListIterator<Type> List<Type>::find(const Type& value) {
        throw ListNotImplementedException(__FILE__, __FUNCTION__, __LINE__);
        return ListIterator<Type>();
    }
    template<typename Type>
    inline ListIterator<const Type> List<Type>::find(const Type& value) const {
        throw ListNotImplementedException(__FILE__, __FUNCTION__, __LINE__);
        return ListIterator<const Type>();
    }
    
    template<typename Type>
    inline Type* List<Type>::toCArray() noexcept {
        //throw ListNotImplementedException(__FILE__, __FUNCTION__, __LINE__);
        return nullptr;
    }
    
    template<typename Type>
    inline ListIterator<const Type> List<Type>::iteratorFromIndex(size_t index) const {
        throw ListNotImplementedException(__FILE__, __FUNCTION__, __LINE__);
        return ListIterator<const Type>();
    }
    template<typename Type>
    inline ListIterator<Type> List<Type>::iteratorFromIndex(size_t index) {
        throw ListNotImplementedException(__FILE__, __FUNCTION__, __LINE__);
        return ListIterator<Type>();
    }
}

template<typename Type>
inline std::ostream& operator<<(std::ostream& stream, const jora::List<Type>& list) {
    return stream << "[List, size=" << list.size() << "]";
}
