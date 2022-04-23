#pragma once
#include <cstdlib>

namespace jora {
    class Container {
    public:
        Container() = default;
        inline Container(size_t size) : _size(size) {}
        inline Container(const Container &other) = delete;
        inline Container(Container &&other) = delete;
        ~Container() = default;

        virtual inline operator bool() { return _size == 0; }

        virtual inline size_t size() { return _size; }

    protected:
        virtual inline void setSize(size_t size) noexcept { _size = size; };

    private:
        size_t _size = 0U;
    };
}
