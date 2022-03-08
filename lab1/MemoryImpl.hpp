#pragma once
#include <memory>
#include "Exit.hpp"

template <typename T>
inline Exit allocImpl(T *&ptr, size_t amount) {
    ptr = static_cast<T *>(malloc(amount * sizeof(T)));
    return ptr ? Exit::success : Exit::noMemory;
}

template <typename T>
inline Exit allocImpl(T *&ptr) {
    ptr = static_cast<T *>(malloc(sizeof(T)));
    return ptr ? Exit::success : Exit::noMemory;
}

template <typename T>
inline Exit reallocImpl(T *&ptr, size_t newSize) {
    T *buff = static_cast<T *>(realloc(ptr, sizeof(T)));
    Exit ec = Exit::success;

    if (buff)
        ptr = buff;
    else
        ec = Exit::noMemory;

    return ec;
}

template <typename T>
inline void freeImpl(T *&ptr) {
    free(ptr);
    ptr = nullptr;
}

template <typename T>
inline void zeroMemory(T *ptr, size_t amount) {
    memset(ptr, 0, amount * sizeof(T));
}

template <typename T>
inline void zeroMemory(T *ptr) {
    memset(ptr, 0, sizeof(T));
}
