#pragma once
#include <memory>

namespace jora {
    template <typename Type>
    struct Node {
    public:
        Node() noexcept = default;
        Node(const Node &other) noexcept {
            this->operator=(other);
        };
        Node(Node &&other) noexcept = default;
        Node(const Type &value, std::shared_ptr<Node> &next = std::shared_ptr<Node>()) noexcept
            : _value(value), _next(next) {}
        ~Node() = default;

        inline Node &operator=(const Node &other) {
            _value = other._value;
            _next = other._next;
            return this;
        }

        inline const Type &value() const noexcept { return _value; }
        inline void setValue(const Type &value) noexcept { _value = value; }

        inline const std::shared_ptr<Node> &next() noexcept { return _next; }
        inline const std::shared_ptr<const Node> &next() const noexcept { return _next; }
        inline void setNext(const std::shared_ptr<Node> &next) { _next = next; }
        inline void setNext(const Node &next) { _next = std::make_shared(next); }

    private:
        Type _value = Type();
        std::shared_ptr<Node> _next = std::shared_ptr<Node>();
    };
}
