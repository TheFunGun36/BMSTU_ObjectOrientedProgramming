#pragma once
#include "Exit.hpp"
#include "Point.hpp"
#include "Projection.hpp"

struct VectorPoint3D {
    size_t allocated;
    size_t size;
    Point3D *arr;
};

struct VectorPolygon {
    size_t allocated;
    size_t size;
    Polygon *arr;
};

struct VectorInt {
    size_t allocated;
    size_t size;
    int *arr;
};

Exit vectorReserve(VectorPoint3D &arr, size_t newSize);
Exit vectorPushBack(VectorPoint3D &arr, const Point3D &val);
void vectorFree(VectorPoint3D &arr);

Exit vectorReserve(VectorPolygon &arr, size_t newSize);
Exit vectorPushBack(VectorPolygon &arr, const Polygon &val);
void vectorFree(VectorPolygon &arr);

Exit vectorPushBack(VectorInt &arr, const int &val);
void vectorFree(VectorInt &arr);
