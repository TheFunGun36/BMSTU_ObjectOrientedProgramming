#pragma once
#include "Exit.hpp"
#include "MemoryImpl.hpp"

const double vectorArrIncCoef = 2.0;

template<typename T>
struct Vector {
    size_t allocated;
    size_t size;
    T *arr;
};

template <typename T>
inline Exit vectorInitialize(Vector<T> &arr, size_t amount) {
    Exit ec = amount ? Exit::success : Exit::sizeInvalid;

    if (isOk(ec))
        ec = allocImpl(arr.arr, amount);

    if (isOk(ec)) {
        arr.size = 0;
        arr.allocated = amount;
    }

    return ec;
}

template <typename T>
inline void vectorFree(Vector<T> &arr) {
    free(arr.arr);
    zeroMemory(&arr);
}

template <typename T>
inline Exit vectorReserve(Vector<T> &arr, size_t newSize) {
    Exit ec = newSize ? Exit::success : Exit::sizeInvalid;

    if (isOk(ec) && arr.allocated < newSize) {
        ec = reallocImpl(arr.arr, newSize);

        if (isOk(ec))
            arr.size = newSize;
    }

    return ec;
}

template <typename T>
inline Exit vectorInc(Vector<T> &arr) {
    size_t newLen = ceil(vectorArrIncCoef * arr.allocated);
    Exit ec = vectorReserve(arr, newLen);

    if (isOk(ec))
        arr.allocated = newLen;

    return ec;
}

template <typename T>
inline Exit vectorPushBack(Vector<T> &arr, const T &val) {
    Exit ec = vectorInc(arr);

    if (isOk(ec)) {
        arr.arr[arr.size] = val;
        arr.size++;
    }

    return ec;
}
