#pragma once
#include <cstring>
#include "Point.hpp"
#include "Projection.hpp"
#include "Exit.hpp"
#include "Vector.hpp"

struct Model3D {
    VectorPoint3D points;
    VectorPolygon faces;
    Point3D center;
};

inline Model3D modelEmpty() {
    Model3D empty;
    memset(&empty, 0, sizeof(Model3D));
    return empty;
}

Exit modelReserveVertex(Model3D &model, size_t amount);
Exit modelReserveFace(Model3D &model, size_t amount);
Exit modelAddVertex(Model3D &model, Point3D vertex);
Exit modelAddFace(Model3D &model, Polygon &face);
void modelClear(Model3D &model);

Exit modelMove(Model3D &model, Vector3D moveVector);
Exit modelRotate(Model3D &model, Vector3D eulerAngles);
Exit modelScale(Model3D &model, Vector3D scaleVector);

Exit modelProjectPerspective(Projection &projection, const Model3D &model, Real cameraDistance);
Exit modelProjectOrthogonal(Projection &projection, const Model3D &model);
