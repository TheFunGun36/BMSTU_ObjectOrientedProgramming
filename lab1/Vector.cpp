#include "Vector.hpp"

Exit vectorReserve(VectorPoint3D &arr, size_t newSize) {
    Exit ec = newSize ? Exit::success : Exit::sizeInvalid;
    if (isOk(ec) && arr.allocated < newSize) {
        auto *buf = (Point3D *)realloc(arr.arr, newSize * sizeof(Point3D));
        if (!buf) {
            ec = Exit::noMemory;
        }
        else {
            arr.allocated = newSize;
            arr.arr = buf;
        }
    }
    return ec;
}

Exit vectorReserve(VectorPolygon &arr, size_t newSize) {
    Exit ec = newSize ? Exit::success : Exit::sizeInvalid;
    if (isOk(ec) && arr.allocated < newSize) {
        auto *buf = (Polygon *)realloc(arr.arr, newSize * sizeof(Polygon));
        if (!buf) {
            ec = Exit::noMemory;
        }
        else {
            arr.allocated = newSize;
            arr.arr = buf;
        }
    }
    return ec;
}

static Exit vectorReserve(VectorInt &arr, size_t newSize) {
    Exit ec = newSize ? Exit::success : Exit::sizeInvalid;
    if (isOk(ec) && arr.allocated < newSize) {
        auto *buf = (int *)realloc(arr.arr, newSize * sizeof(int));
        if (!buf) {
            ec = Exit::noMemory;
        }
        else {
            arr.allocated = newSize;
            arr.arr = buf;
        }
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
    memset(&arr, 0, sizeof(VectorPoint3D));
}

void vectorFree(VectorPolygon &arr) {
    free(arr.arr);
    memset(&arr, 0, sizeof(VectorPolygon));
}

void vectorFree(VectorInt &arr) {
    free(arr.arr);
    memset(&arr, 0, sizeof(VectorInt));
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