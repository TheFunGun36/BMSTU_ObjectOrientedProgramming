#pragma once
#include <memory>
#include "jnodeexception.h"

namespace jora {
    template <typename Type>
    class Node : public Container {
        using NodeT = typename std::conditional<std::is_const<Type>::value, const Node<Type>, Node<Type>>::type;
    public:
        Node() noexcept = default;
        Node(const Node<Type>& other) noexcept;
        Node(const Type& value, const std::shared_ptr<Node<Type>>& next = std::shared_ptr<Node<Type>>()) noexcept;
        ~Node() = default;

        inline Node<Type>& operator=(const Node<Type>& other);

        const Type& value() const noexcept;
        Type& value() noexcept;

        const std::shared_ptr<Node<Type>>& next() noexcept;
        const std::shared_ptr<const Node<Type>>& next() const noexcept;
        void setNext(const std::shared_ptr<Node<Type>>& next) noexcept;
        void setNext(const Node<Type>& next);

        static std::shared_ptr<Node<Type>> create(const Type& val = Type(), const std::shared_ptr<Node<Type>>& next = nullptr);
        static std::shared_ptr<Node<Type>> create(const Node<Type>& node);

        virtual size_t size() const noexcept override;
        virtual operator bool() const noexcept override;
        virtual void clear() override;

    private:
        Type _value = Type();
        std::shared_ptr<NodeT> _next = std::shared_ptr<NodeT>();
    };


    /********** IMPLEMENTATION **********/
    template<typename Type>
    inline Node<Type>::Node(const Node<Type>& other) noexcept {
        this->operator=(other);
    }
    template<typename Type>
    inline Node<Type>::Node(const Type& value, const std::shared_ptr<Node<Type>>& next) noexcept
        : _value(value), _next(next) {}
    template<typename Type>
    inline Node<Type>& Node<Type>::operator=(const Node<Type>& other) {
        _value = other._value;
        _next = other._next;
        return *this;
    }
    template<typename Type>
    inline const Type& Node<Type>::value() const noexcept {
        return _value;
    }
    template<typename Type>
    inline Type& Node<Type>::value() noexcept {
        return _value;
    }
    template<typename Type>
    inline const std::shared_ptr<Node<Type>>& Node<Type>::next() noexcept {
        return _next;
    }
    template<typename Type>
    inline const std::shared_ptr<const Node<Type>>& Node<Type>::next() const noexcept {
        return _next;
    }
    template<typename Type>
    inline void Node<Type>::setNext(const std::shared_ptr<Node<Type>>& next) noexcept {
        _next = next;
    }
    template<typename Type>
    inline void Node<Type>::setNext(const Node<Type>& next) {
        _next = Node<Type>::create(next);
    }
    template<typename Type>
    inline std::shared_ptr<Node<Type>> Node<Type>::create(const Type& val, const std::shared_ptr<Node<Type>>& next) {
        std::shared_ptr<Node<Type>> result;
        try {
            result = std::make_shared<Node<Type>>(val, next);
        }
        catch (const std::bad_alloc&) {
            throw NodeBadAllocException(__FILE__, __FUNCTION__, __LINE__);
        }
        return result;
    }
    template<typename Type>
    inline std::shared_ptr<Node<Type>> Node<Type>::create(const Node<Type>& node) {
        std::shared_ptr<Node<Type>> result;
        try {
            result = std::make_shared<Node<Type>>(node);
        }
        catch (const std::bad_alloc& e) {
            throw NodeBadAllocException(__FILE__, __FUNCTION__, __LINE__);
        }
        return result;
    }
    template<typename Type>
    inline size_t Node<Type>::size() const noexcept {
        return 1;
    }
    template<typename Type>
    inline Node<Type>::operator bool() const noexcept {
        return true;
    }
    template<typename Type>
    inline void Node<Type>::clear() {
        setNext(nullptr);
    }
}
