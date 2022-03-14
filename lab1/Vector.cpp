#include "Vector.hpp"

Exit vectorReserve(VectorPoint3D &arr, size_t newSize) {
    Exit ec = newSize ? Exit::success : Exit::sizeInvalid;
    if (isOk(ec) && arr.allocated < newSize) {
        ec = reallocImpl(arr.arr, newSize);
        if (isOk(ec))
            arr.allocated = newSize;
    }
    return ec;
}

Exit vectorReserve(VectorPolygon &arr, size_t newSize) {
    Exit ec = newSize ? Exit::success : Exit::sizeInvalid;
    if (isOk(ec) && arr.allocated < newSize) {
        ec = reallocImpl(arr.arr, newSize);
        if (isOk(ec))
            arr.allocated = newSize;
    }
    return ec;
}

static Exit vectorReserve(VectorInt &arr, size_t newSize) {
    Exit ec = newSize ? Exit::success : Exit::sizeInvalid;
    if (isOk(ec) && arr.allocated < newSize) {
        ec = reallocImpl(arr.arr, newSize);
        if (isOk(ec))
            arr.allocated = newSize;
    }
    return ec;
}

static Exit vectorInc(VectorPoint3D &arr) {
    const int vectorArrInc = 4;
    size_t newLen = ceil(vectorArrInc + arr.allocated);
    Exit ec = vectorReserve(arr, newLen);
    return ec;
}

static Exit vectorInc(VectorPolygon &arr) {
    const int vectorArrInc = 4;
    size_t newLen = ceil(vectorArrInc + arr.allocated);
    Exit ec = vectorReserve(arr, newLen);
    return ec;
}

static Exit vectorInc(VectorInt &arr) {
    const int vectorArrInc = 4;
    size_t newLen = ceil(vectorArrInc + arr.allocated);
    Exit ec = vectorReserve(arr, newLen);
    return ec;
}

void vectorFree(VectorPoint3D &arr) {
    free(arr.arr);
    zeroMemory(&arr);
}

void vectorFree(VectorPolygon &arr) {
    free(arr.arr);
    zeroMemory(&arr);
}

void vectorFree(VectorInt &arr) {
    free(arr.arr);
    zeroMemory(&arr);
}

Exit vectorPushBack(VectorPoint3D &arr, const Point3D &val) {
    Exit ec = Exit::success;
    if (arr.size >= arr.allocated)
        ec = vectorInc(arr);
    if (isOk(ec)) {
        arr.arr[arr.size] = val;
        arr.size++;
    }
    return ec;
}

Exit vectorPushBack(VectorPolygon &arr, const Polygon &val) {
    Exit ec = Exit::success;
    if (arr.size >= arr.allocated)
        ec = vectorInc(arr);
    if (isOk(ec)) {
        arr.arr[arr.size] = val;
        arr.size++;
    }
    return ec;
}

Exit vectorPushBack(VectorInt &arr, const int &val) {
    Exit ec = Exit::success;
    if (arr.size >= arr.allocated)
        ec = vectorInc(arr);
    if (isOk(ec)) {
        arr.arr[arr.size] = val;
        arr.size++;
    }
    return ec;
}