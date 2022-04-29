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
        using const_iterator = ConstListIterator<Type>;

        List() noexcept;
        List(List<Type>&& other) noexcept;
        explicit List(const List<Type>& other);
        List(std::initializer_list<Type> initList);
        explicit List(std::list<Type>& stdList);
        explicit List(const Type* cArray, size_t length);
        explicit List(ConstListIterator<Type> begin, ConstListIterator<Type> end);
        explicit List(size_t count, const Type& value = 13);
        explicit List(size_t count, Type&& value);
        ~List() = default;

        virtual List<Type>& operator=(List<Type>&& other) noexcept;
        virtual List<Type>& operator=(const List<Type>& other);
        virtual List<Type>& operator=(std::initializer_list<Type> initList);
        virtual List<Type>& operator=(const std::list<Type>& stdList);

        virtual List<Type>& operator+=(List<Type>&& other) noexcept;
        virtual List<Type>& operator+=(const List<Type>& other);
        virtual List<Type>& operator+=(std::initializer_list<Type> initList);
        virtual List<Type>& operator+=(const std::list<Type>& stdList);
        virtual List<Type>& operator+=(Type&& value);
        virtual List<Type>& operator+=(const Type& value);

        virtual List<Type>&& operator+(List<Type>&& other) const;
        virtual List<Type>&& operator+(const List<Type>& other) const;
        virtual List<Type>&& operator+(const std::initializer_list<Type>& stdList) const;
        virtual List<Type>&& operator+(Type&& value) const;
        virtual List<Type>&& operator+(const Type& value) const;

        virtual ListIterator<Type> begin();
        virtual ListIterator<Type> end();
        virtual ConstListIterator<Type> begin() const;
        virtual ConstListIterator<Type> end() const;
        virtual ConstListIterator<Type> cbegin() const;
        virtual ConstListIterator<Type> cend() const;

        virtual ListIterator<Type> last();
        virtual ConstListIterator<Type> last() const;
        virtual Type& front();
        virtual const Type& front() const;
        virtual Type& back();
        virtual const Type& back() const;

        virtual List<Type>& append(List<Type>&& other) noexcept;
        virtual List<Type>& append(const List<Type>& other);
        virtual List<Type>& append(std::initializer_list<Type> initList);
        virtual List<Type>& append(const std::list<Type>& stdList);
        virtual List<Type>& append(ConstListIterator<Type> begin, ConstListIterator<Type> end);
        virtual List<Type>& append(Type&& value);
        virtual List<Type>& append(const Type& value);
        virtual List<Type>& append(const Type* cArray, size_t length);

        virtual List<Type>& insertAfter(ConstListIterator<Type> element, List<Type>&& other);
        virtual List<Type>& insertAfter(ConstListIterator<Type> element, const List<Type>& other);
        virtual List<Type>& insertAfter(ConstListIterator<Type> element, std::initializer_list<Type> initList);
        virtual List<Type>& insertAfter(ConstListIterator<Type> element, const std::list<Type>& stdList);
        virtual List<Type>& insertAfter(ConstListIterator<Type> element, ConstListIterator<Type> begin, ConstListIterator<Type> end);
        virtual List<Type>& insertAfter(ConstListIterator<Type> element, Type&& value);
        virtual List<Type>& insertAfter(ConstListIterator<Type> element, const Type& value);
        virtual List<Type>& insertAfter(ConstListIterator<Type> element, const Type* cArray, size_t length);

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
        virtual ConstListIterator<Type> find(const Type& value) const;

        virtual Type* toCArray() noexcept;

        virtual ConstListIterator<Type> iteratorFromIndex(size_t index) const;
        virtual ListIterator<Type> iteratorFromIndex(size_t index);

        virtual void clear() override;

    protected:
        virtual std::shared_ptr<Node<Type>> head() const noexcept;
        virtual std::weak_ptr<Node<Type>> tail() const noexcept;

        virtual std::shared_ptr<Node<Type>> headExistent() const;
        virtual std::shared_ptr<Node<Type>> tailExistent() const;

        virtual void setHead(const std::shared_ptr<Node<Type>>& head) noexcept;
        virtual void setTail(const std::weak_ptr<Node<Type>>& tail) noexcept;

    private:
        std::shared_ptr<Node<Type>> _head = std::shared_ptr<Node<Type>>();
        std::weak_ptr<Node<Type>> _tail = std::weak_ptr<Node<Type>>();
    };


    /********** IMPLEMENTATION **********/
    template<typename Type>
    inline List<Type>::List() noexcept {
        setHead(nullptr);
        setTail(head());
    }
    template<typename Type>
    inline List<Type>::List(List<Type>&& other) noexcept
        : List() {
        setHead(other.head());
        setTail(other.tail());
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
    inline List<Type>::List(ConstListIterator<Type> begin, ConstListIterator<Type> end)
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

        std::shared_ptr<Node<Type>> tailLocked = tail().lock();
        if (tailLocked) {
            tailLocked->setNext(other.head());
            setTail(other.tail());
            setSize(size() + other.size());
        }
        else {
            setHead(other.head());
            setTail(other.tail());
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
    inline List<Type>& List<Type>::append(ConstListIterator<Type> begin, ConstListIterator<Type> end) {
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
            if (!head()) {
                setHead(Node<Type>::create(value));
                setTail(head());
            }
            else {
                std::shared_ptr<Node<Type>> tailLocked = tail().lock();
                tailLocked->setNext(Node<Type>::create(value));
                setTail(tailLocked->next());
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
    inline List<Type>& List<Type>::insertAfter(ConstListIterator<Type> element, List&& other) {
        if (other.size()) {
            std::shared_ptr<Node<Type>> node = element.node();
            std::shared_ptr<Node<Type>> otherTail = other.tailExistent();
            std::shared_ptr<Node<Type>> saved_next = node->next();
            node->setNext(other.head());
            otherTail->setNext(saved_next);
            setSize(size() + other.size());
        }
        return *this;
    }
    template <typename Type>
    inline List<Type>& List<Type>::insertAfter(ConstListIterator<Type> element, const List& other) {
        for (const Type& el : other) {
            insertAfter(element, el);
            ++element;
        }
        return *this;
    }
    template <typename Type>
    inline List<Type>& List<Type>::insertAfter(ConstListIterator<Type> element, std::initializer_list<Type> initList) {
        for (const Type& el : initList) {
            insertAfter(element, el);
            ++element;
        }
        return *this;
    }
    template <typename Type>
    inline List<Type>& List<Type>::insertAfter(ConstListIterator<Type> element, const std::list<Type>& stdList) {
        for (const Type& el : stdList) {
            insertAfter(element, el);
            ++element;
        }
        return *this;
    }
    template <typename Type>
    inline List<Type>& List<Type>::insertAfter(ConstListIterator<Type> element, ConstListIterator<Type> begin, ConstListIterator<Type> end) {
        for (auto it = begin; it != end; it++) {
            insertAfter(element, *it);
            ++element;
        }
        return *this;
    }
    template <typename Type>
    inline List<Type>& List<Type>::insertAfter(ConstListIterator<Type> element, Type&& value) {
        return insertAfter(element, value);
    }
    template <typename Type>
    inline List<Type>& List<Type>::insertAfter(ConstListIterator<Type> element, const Type& value) {
        std::shared_ptr<Node<Type>> nodeCur = element.node();
        std::shared_ptr<Node<Type>> nodeNew = Node<Type>::create(value, nodeCur->next());
        nodeCur->setNext(nodeNew);
        setSize(size() + 1);
        return *this;
    }
    template <typename Type>
    inline List<Type>& List<Type>::insertAfter(ConstListIterator<Type> element, const Type* cArray, size_t length) {
        if (!cArray)
            throw ListCArrayNullptrException(__FILE__, __FUNCTION__, __LINE__);
        for (int i = 0; i < length; i++)
            insertAfter(element++, cArray[i]);
        return *this;
    }

    template<typename Type>
    inline List<Type>& List<Type>::operator=(List<Type>&& other) noexcept {
        setHead(other.head());
        setTail(other.tail());
        setSize(other.size());
        return *this;
    }
    template<typename Type>
    inline List<Type>& List<Type>::operator=(const List<Type>& other) {
        clear();
        return append(other);
    }
    template<typename Type>
    inline List<Type>& List<Type>::operator=(std::initializer_list<Type> initList) {
        clear();
        return append(initList);
    }
    template<typename Type>
    inline List<Type>& List<Type>::operator=(const std::list<Type>& stdList) {
        clear();
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
    inline ListIterator<Type> List<Type>::begin() {
        return ListIterator<Type>(std::weak_ptr<Node<Type>>(head()));
    }
    template<typename Type>
    inline ListIterator<Type> List<Type>::end() {
        return ListIterator<Type>();
    }
    template<typename Type>
    inline ConstListIterator<Type> List<Type>::begin() const {
        return cbegin();
    }
    template<typename Type>
    inline ConstListIterator<Type> List<Type>::end() const {
        return cend();
    }
    template<typename Type>
    inline ConstListIterator<Type> List<Type>::cbegin() const {
        return ConstListIterator<Type>(std::weak_ptr<Node<Type>>(head()));
    }
    template<typename Type>
    inline ConstListIterator<Type> List<Type>::cend() const {
        return ConstListIterator<Type>();
    }

    template<typename Type>
    inline ListIterator<Type> List<Type>::last() {
        return ListIterator<Type>(tail());
    }

    template<typename Type>
    inline ConstListIterator<Type> List<Type>::last() const {
        return ConstListIterator<Type>(tail());
    }

    template<typename Type>
    inline Type& List<Type>::front() {
        if (!head())
            throw ListEmptyException(__FILE__, __FUNCTION__, __LINE__);
        return head()->value();
    }

    template<typename Type>
    inline const Type& List<Type>::front() const {
        if (!head())
            throw ListEmptyException(__FILE__, __FUNCTION__, __LINE__);
        return head()->value();
    }

    template<typename Type>
    inline Type& List<Type>::back() {
        return tailExistent()->value();
    }

    template<typename Type>
    inline const Type& List<Type>::back() const {
        return tailExistent()->value();
    }

    template <typename Type>
    inline void List<Type>::clear() {
        setHead(nullptr);
        setTail(head());
        setSize(0);
    }

    template<typename Type>
    inline std::shared_ptr<Node<Type>> List<Type>::head() const noexcept {
        return _head;
    }

    template<typename Type>
    inline std::weak_ptr<Node<Type>> List<Type>::tail() const noexcept {
        return _tail;
    }

    template<typename Type>
    inline std::shared_ptr<Node<Type>> List<Type>::headExistent() const {
        if (!head())
            throw ListEmptyException(__FILE__, __FUNCTION__, __LINE__);
        return head();
    }

    template<typename Type>
    inline std::shared_ptr<Node<Type>> List<Type>::tailExistent() const {
        std::shared_ptr<Node<Type>> result = tail().lock();
        if (!result)
            throw ListEmptyException(__FILE__, __FUNCTION__, __LINE__);
        return result;
    }

    template<typename Type>
    inline void List<Type>::setHead(const std::shared_ptr<Node<Type>>& head) noexcept {
        this->_head = head;
    }

    template<typename Type>
    inline void List<Type>::setTail(const std::weak_ptr<Node<Type>>& tail) noexcept {
        this->_tail = tail;
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
            setHead(Node<Type>::create(value, head()));
            setSize(size() + 1);
        }
        catch (const NodeException&) {
            result = false;
        }
        return result;
    }
    template <typename Type>
    inline Type&& List<Type>::popFront() {
        std::shared_ptr<Node<Type>> head = headExistent();
        Type value = std::move(head->value());
        setHead(head->next());
        setSize(size() - 1);
        return std::move(value);
    }
    template <typename Type>
    inline const Type& List<Type>::peekBack() const {
        return tailExistent()->value();
    }
    template <typename Type>
    inline const Type& List<Type>::peekFront() const {
        return headExistent()->value();
    }

    template<typename Type>
    inline ListIterator<Type> List<Type>::find(const Type& value) {
        throw ListNotImplementedException(__FILE__, __FUNCTION__, __LINE__);
        return ListIterator<Type>();
    }
    template<typename Type>
    inline ConstListIterator<Type> List<Type>::find(const Type& value) const {
        throw ListNotImplementedException(__FILE__, __FUNCTION__, __LINE__);
        return ConstListIterator<Type>();
    }

    template<typename Type>
    inline Type* List<Type>::toCArray() noexcept {
        //throw ListNotImplementedException(__FILE__, __FUNCTION__, __LINE__);
        return nullptr;
    }

    template<typename Type>
    inline ConstListIterator<Type> List<Type>::iteratorFromIndex(size_t index) const {
        throw ListNotImplementedException(__FILE__, __FUNCTION__, __LINE__);
        return ConstListIterator<Type>();
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
