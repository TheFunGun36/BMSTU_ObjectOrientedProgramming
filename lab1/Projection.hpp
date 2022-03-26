#pragma once
#include "Point.hpp"
#include "Exit.hpp"

struct Polygon {
    size_t verticiesAmount;
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
Exit polygonCopy(Polygon &dst, const Polygon &src);
void polygonFree(Polygon &p);
void projectionFree(Projection &p);
Projection projectionEmpty();
