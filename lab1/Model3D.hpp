#pragma once
#include "Point.hpp"
#include "Projection.hpp"
#include "Exit.hpp"

struct Model3D;

Exit modelInitialize(Model3D *&model);
Exit modelReserveVertex(Model3D *model, size_t amount);
Exit modelReserveFace(Model3D *model, size_t amount);
Exit modelAddVertex(Model3D *model, Point3D vertex);
Exit modelAddFace(Model3D *model, Polygon &face);
Exit modelClear(Model3D *model);

Exit modelMove(Model3D *model, Vector3D moveVector);
Exit modelRotate(Model3D *model, Vector3D eulerAngles);
Exit modelScale(Model3D *model, Vector3D scaleVector);

void modelFree(Model3D *&model);

Exit modelProjectPerspective(Projection *&projection, const Model3D *model, double cameraDistance);
Exit modelProjectOrthogonal(Projection *&projection, const Model3D *model);
