#include "Model3D.hpp"
#include <cassert>
#include <cmath>
#include "Vector.hpp"

struct Model3D {
    VectorPoint3D points;
    VectorPolygon faces;
    Point3D center;
};

Exit modelInitialize(Model3D *&model) {
    Exit ec = Exit::success;

    if (model) {
        ec = Exit::modelInitialized;
    }
    else {
        model = (Model3D *)malloc(sizeof(Model3D));
        ec = model ? Exit::success : Exit::noMemory;
    }

    if (isOk(ec))
        memset(model, 0, sizeof(Model3D));

    return ec;
}

Exit modelReserveVertex(Model3D *model, size_t amount) {
    Exit ec = Exit::success;

    if (!model)
        ec = Exit::modelUnininialized;
    else
        ec = vectorReserve(model->points, amount);

    return ec;
}

Exit modelReserveFace(Model3D *model, size_t amount) {
    Exit ec = Exit::success;

    if (!model)
        ec = Exit::modelUnininialized;
    else
        ec = vectorReserve(model->faces, amount);

    return ec;
}

Exit modelAddVertex(Model3D *model, Point3D vertex) {
    Exit ec = Exit::success;

    if (!model)
        ec = Exit::modelUnininialized;
    else
        ec = vectorPushBack(model->points, vertex);

    return ec;
}

Exit modelAddFace(Model3D *model, Polygon &face) {
    Exit ec = Exit::success;

    if (!model)
        ec = Exit::modelUnininialized;
    else
        ec = vectorPushBack(model->faces, face);

    if (isOk(ec))
        memset(&face, 0, sizeof(Polygon));

    return ec;
}

Exit modelClear(Model3D *model) {
    Exit ec = Exit::success;

    if (!model) {
        ec = Exit::modelUnininialized;
    }
    else {
        vectorFree(model->points);
        for (int i = 0; i < model->faces.size; i++)
            polygonFree(model->faces.arr[i]);
        vectorFree(model->faces);
    }

    return ec;
}

Exit modelMove(Model3D *model, Vector3D moveVector) {
    Exit ec = Exit::success;

    if (!model) {
        ec = Exit::modelUnininialized;
    }
    else {
        for (int i = 0; i < model->points.size; i++) {
            model->points.arr[i].x += moveVector.x;
            model->points.arr[i].y += moveVector.y;
            model->points.arr[i].z += moveVector.z;
        }

        model->center.x += moveVector.x;
        model->center.y += moveVector.y;
        model->center.z += moveVector.z;
    }

    return ec;
}

static void modelRotateX(Model3D &model, Real angle) {
    Real sinx = sin(angle);
    Real cosx = cos(angle);
    for (int i = 0; i < model.points.size; i++) {
        Point3D &p = model.points.arr[i];
        Point3D &c = model.center;
        Real dy = p.y - c.y;
        Real dz = p.z - c.z;
        p.y = c.y + dy * cosx + dz * sinx;
        p.z = c.z - dy * sinx + dz * cosx;
    }
}

static void modelRotateY(Model3D &model, Real angle) {
    Real siny = sin(angle);
    Real cosy = cos(angle);
    for (int i = 0; i < model.points.size; i++) {
        Point3D &p = model.points.arr[i];
        Point3D &c = model.center;
        Real dx = p.x - c.x;
        Real dz = p.z - c.z;
        p.x = c.x + dx * cosy + dz * siny;
        p.z = c.z - dx * siny + dz * cosy;
    }
}

static void modelRotateZ(Model3D &model, Real angle) {
    Real sinz = sin(angle);
    Real cosz = cos(angle);
    for (int i = 0; i < model.points.size; i++) {
        Point3D &p = model.points.arr[i];
        Point3D &c = model.center;
        Real dx = p.x - c.x;
        Real dy = p.y - c.y;
        p.x = c.x + dx * cosz + dy * sinz;
        p.y = c.y - dx * sinz + dy * cosz;
    }
}

Exit modelRotate(Model3D *model, Vector3D eulerAngles, bool reverse) {
    Exit ec = Exit::success;

    if (!model) {
        ec = Exit::modelUnininialized;
    }
    else {
        if (reverse) {
            modelRotateZ(*model, eulerAngles.z);
            modelRotateY(*model, eulerAngles.y);
            modelRotateX(*model, eulerAngles.x);
        }
        else {
            modelRotateX(*model, eulerAngles.x);
            modelRotateY(*model, eulerAngles.y);
            modelRotateZ(*model, eulerAngles.z);
        }
    }

    return ec;
}

Exit modelScale(Model3D *model, Vector3D scaleVector) {
    Exit ec = Exit::success;

    if (!model) {
        ec = Exit::modelUnininialized;
    }
    else if (isZero(scaleVector.x) || isZero(scaleVector.y) || isZero(scaleVector.z)) {
        ec = Exit::modelScaleZero;
    }
    else {
        for (int i = 0; i < model->points.size; i++) {
            Point3D &p = model->points.arr[i];
            Point3D &c = model->center;

            p.x = c.x + (p.x - c.x) * scaleVector.x;
            p.y = c.y + (p.y - c.y) * scaleVector.y;
            p.z = c.z + (p.z - c.z) * scaleVector.z;
        }
    }

    return ec;
}

void modelFree(Model3D *&model) {
    if (model) {
        modelClear(model);
        free(model);
        model = nullptr;
    }
}

static Exit projectionAllocFaces(Projection &projection, const Model3D &model) {
    size_t facesAmount = model.faces.size;
    Exit ec = Exit::success;

    int i = 0;
    while (isOk(ec) && i < facesAmount) {
        Polygon *dst = projection.polygonArray + i;
        Polygon *src = model.faces.arr + i;

        dst->vertexIndexArray = (size_t *)malloc(src->amount * sizeof(size_t));
        ec = dst->vertexIndexArray ? Exit::success : Exit::noMemory;
        i++;
    }

    if (!isOk(ec)) {
        i -= 2;
        while (i > 0) {
            free(projection.polygonArray[i].vertexIndexArray);
            i--;
        }
    }

    return ec;
}

static void projectionCopyPoints(Projection &projection, const VectorPoint3D points) {
    size_t pointsAmount = points.size;
    for (int i = 0; i < pointsAmount; i++) {
        projection.pointArray[i].x = points.arr[i].x;
        projection.pointArray[i].y = -points.arr[i].y;
    }
}

static void projectionCopyVerticies(Projection &projection, const VectorPolygon faces) {
    for (int i = 0; i < projection.polygonAmount; i++) {
        for (int j = 0; j < faces.arr[i].amount; j++)
            projection.polygonArray[i].vertexIndexArray[j] = faces.arr[i].vertexIndexArray[j];
        projection.polygonArray[i].amount = faces.arr[i].amount;
    }
}

Exit modelProjectOrthogonal(Projection &projection, const Model3D *model) {
    Exit ec = model ? Exit::success : Exit::modelUnininialized;

    if (isOk(ec)) {
        projection.pointArray = (Point2D *)malloc(model->points.size * sizeof(Point2D));
        ec = projection.pointArray ? Exit::success : Exit::noMemory;
    }
    if (isOk(ec)) {
        projection.polygonArray = (Polygon *)malloc(model->faces.size * sizeof(Polygon));
        ec = projection.polygonArray ? Exit::success : Exit::noMemory;
    }

    if (isOk(ec)) {
        int i = 0;
        ec = projectionAllocFaces(projection, *model);
    }

    if (isOk(ec)) {
        projection.pointsAmount = model->points.size;
        projection.polygonAmount = model->faces.size;

        projection.center.x = model->center.x;
        projection.center.y = model->center.y;

        projectionCopyPoints(projection, model->points);
        projectionCopyVerticies(projection, model->faces);
    }

    if (!isOk(ec)) {
        projectionFree(projection);
        memset(&projection, 0, sizeof(Projection));
    }

    return ec;
}

static inline bool isCameraDistanceValid(const Model3D &model, Real cameraDistance) {
    bool valid = true;
    static const Real cameraPointBufferDistance = 30;

    Point3D *p = model.points.arr;
    while (valid && p < model.points.arr + model.points.size) {
        valid = p->z < cameraDistance - cameraPointBufferDistance;
        p++;
    }

    valid = valid && model.center.z < cameraDistance - cameraPointBufferDistance;

    return valid;
}

Exit modelProjectPerspective(Projection &projection, const Model3D *model, Real cameraDistance) {
    Exit ec = Exit::success;

    if (!model) {
        ec = Exit::modelUnininialized;
    }
    else if (!isCameraDistanceValid(*model, cameraDistance)) {
        ec = Exit::inputCameraTooClose;
    }
    else {
        ec = modelProjectOrthogonal(projection, model);
    }

    if (isOk(ec)) {
        Real k = cameraDistance / (-model->center.z + cameraDistance);
        projection.center.x *= k;
        projection.center.y *= k;

        for (int i = 0; i < projection.pointsAmount; i++) {
            k = cameraDistance / (-model->points.arr[i].z + cameraDistance);
            projection.pointArray[i].x *= k;
            projection.pointArray[i].y *= k;
        }
    }

    return ec;
}
