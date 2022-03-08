#pragma once
#include "Point.hpp"
#include "Exit.hpp"

struct Polygon {
    size_t amount;
    size_t *vertexIndexArray;
};

struct Projection {
    size_t pointsAmount;
    Point2D *pointArray;

    size_t polygonAmount;
    Polygon *polygonArray;
    Point2D center;
};

Exit polygonCreate(Polygon &p, size_t size);
void polygonFree(Polygon &p);
