#pragma once
#include "jiterator.h"

namespace jora {
    template <typename Type>
    class Container {
    public:
        using iterator = Iterator<Type>;
        using const_iterator = ConstIterator<Type>;

        Container() = default;
        inline Container(size_t size) : _size(size) {}
        inline Container(const Container &other) = delete;
        inline Container(Container &&other) = delete;
        ~Container() = default;

        virtual inline operator bool() { return size == 0; };

        // PROPERTIES
        virtual inline size_t size() { return _size; };

    protected:
        virtual inline void setSize(size_t size) noexcept { _size = size; };

    private:
        size_t _size = 0U;
    };
}
