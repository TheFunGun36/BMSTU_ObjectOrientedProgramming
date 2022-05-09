#pragma once
#include <cstdlib>

namespace jora {
    class Container {
    public:
        Container() = default;
        inline Container(size_t size);
        inline Container(const Container &other) = delete;
        inline Container(Container &&other) = delete;
        ~Container() = default;

        virtual inline size_t size() const noexcept;
        virtual inline operator bool() const noexcept;
        virtual inline void clear() = 0;

    protected:
        virtual inline void setSize(size_t size) noexcept;

    private:
        size_t _size = 0U;
    };


    /********** IMPLEMENTATION **********/
    inline Container::Container(size_t size) : _size(size) {}
    inline size_t Container::size() const noexcept {
        return _size;
    }
    inline Container::operator bool() const noexcept {
        return size();
    }
    inline void Container::setSize(size_t size) noexcept {
        _size = size;
    }
}
