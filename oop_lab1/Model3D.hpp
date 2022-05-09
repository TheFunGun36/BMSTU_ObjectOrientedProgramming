#pragma once
#include <cstring>
#include "Point.hpp"
#include "Projection.hpp"
#include "Exit.hpp"
#include "Vector.hpp"
#include "ParamTypes.hpp"

struct Model3D {
    VectorPoint3D points;
    VectorPolygon faces;
    Point3D center;
};

enum class ModelElementType {
    undefined,
    vertex,
    face,
};

struct ModelElement {
    ModelElementType type;

    union Data {
        Point3D vertex;
        Polygon polygon;
    };

    Data data;
};

inline Model3D modelEmpty() {
    Model3D empty;
    memset(&empty, 0, sizeof(Model3D));
    return empty;
}

Exit modelReserveVertex(VAR VectorPoint3D &model, IN size_t amount);
Exit modelReserveFace(VAR VectorPolygon &model, IN size_t amount);
Exit modelAddVertex(VAR VectorPoint3D &model, IN Point3D vertex);
Exit modelAddFace(VAR VectorPolygon &model, VAR Polygon &face);
Exit modelAddElement(VAR Model3D &model, VAR ModelElement &element);
void modelClear(VAR Model3D &model);

Exit modelMove(VAR Model3D &model, IN Vector3D moveVector);
Exit modelRotate(VAR Model3D &model, IN Vector3D eulerAngles);
Exit modelScale(VAR Model3D &model, IN Vector3D scaleVector);
Exit modelValidate(IN const Model3D &model);

Exit modelProjectPerspective(OUT Projection &projection, IN const Model3D &model, IN double cameraDistance);
Exit modelProjectOrthogonal(OUT Projection &projection, IN const Model3D &model);
