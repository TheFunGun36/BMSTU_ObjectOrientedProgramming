#pragma once
#include <memory>
#include "jnodeexception.h"

namespace jora {
    template <typename Type>
    struct Node {
    public:
        Node() noexcept = default;
        Node(const Node& other) noexcept {
            this->operator=(other);
        };
        Node(Node&& other) noexcept = default;
        Node(const Type& value, std::shared_ptr<Node>& next = std::shared_ptr<Node>()) noexcept
            : _value(value), _next(next) {}
        ~Node() = default;

        inline Node& operator=(const Node& other) {
            _value = other._value;
            _next = other._next;
            return *this;
        }

        inline const Type& value() const noexcept { return _value; }
        inline Type& value() noexcept { return _value; }
        inline void setValue(const Type& value) noexcept { _value = value; }

        inline const std::shared_ptr<Node>& next() noexcept { return _next; }
        inline const std::shared_ptr<const Node>& next() const noexcept { return _next; }
        inline void setNext(const std::shared_ptr<Node>& next) noexcept { _next = next; }
        inline void setNext(const Node& next) { _next = Node::create(next); }

        static std::shared_ptr<Node<Type>> create(const Type &val = Type(), const std::shared_ptr<Node<Type>> &next = nullptr) {
            std::shared_ptr<Node<Type>> result;
            try {
                result = std::make_shared<Node<Type>>(val, next);
            }
            catch (const std::bad_alloc &e) {
                throw NodeBadAllocException(__FILE__, __FUNCTION__, __LINE__);
            }
            return result;
        }
        static std::shared_ptr<Node<Type>> create(const Node &node) {
            std::shared_ptr<Node<Type>> result;
            try {
                result = std::make_shared<Node<Type>>(node);
            }
            catch (const std::bad_alloc& e) {
                throw NodeBadAllocException(__FILE__, __FUNCTION__, __LINE__);
            }
            return result;
        }

    private:
        Type _value = Type();
        std::shared_ptr<Node> _next = std::shared_ptr<Node>();
    };
}
