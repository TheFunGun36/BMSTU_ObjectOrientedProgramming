#include "Model3D.hpp"
#include <cassert>
#include <cmath>
#include "Vector.hpp"

#include <qdebug.h>

struct CalculatedAngles {
    Real sinx;
    Real cosx;
    Real siny;
    Real cosy;
    Real sinz;
    Real cosz;
};

Exit modelReserveVertex(Model3D &model, size_t amount) {
    return vectorReserve(model.points, amount);
}

Exit modelReserveFace(Model3D &model, size_t amount) {
    return vectorReserve(model.faces, amount);
}

Exit modelAddVertex(Model3D &model, Point3D vertex) {
    return vectorPushBack(model.points, vertex);
}

Exit modelAddFace(Model3D &model, Polygon &face) {
    Exit ec = vectorPushBack(model.faces, face);
    if (isOk(ec)) memset(&face, 0, sizeof(Polygon));
    return ec;
}

static void clearFaces(VectorPolygon &faces) {
    for (size_t i = 0; i < faces.size; i++)
        polygonFree(faces.arr[i]);
    vectorFree(faces);
}

void modelClear(Model3D &model) {
    vectorFree(model.points);
    clearFaces(model.faces);
}

static Exit moveEveryPoint(VectorPoint3D &points, Vector3D moveVector) {
    Exit ec = points.arr ? Exit::success : Exit::modelUnininialized;

    if (isOk(ec)) {
        for (size_t i = 0; i < points.size; i++)
            points.arr[i] = vector3DAdd(points.arr[i], moveVector);
    }

    return ec;
}

Exit modelMove(Model3D &model, Vector3D moveVector) {
    Exit ec = moveEveryPoint(model.points, moveVector);
    if (isOk(ec))
        model.center = vector3DAdd(model.center, moveVector);
    return ec;
}

static inline Point3D rotatePointX(Point3D point, Real sinx, Real cosx) {
    Point3D result;
    result.x = point.x;
    result.y = +point.y * cosx + point.z * sinx;
    result.z = -point.y * sinx + point.z * cosx;
    return result;
}

static inline Point3D rotatePointY(Point3D point, Real siny, Real cosy) {
    Point3D result;
    result.x = +point.x * cosy + point.z * siny;
    result.y = point.y;
    result.z = -point.x * siny + point.z * cosy;
    return result;
}

static inline Point3D rotatePointZ(Point3D point, Real sinz, Real cosz) {
    Point3D result;
    result.x = +point.x * cosz + point.y * sinz;
    result.y = -point.x * sinz + point.y * cosz;
    result.z = point.z;
    return result;
}

static void rotatePoint(Point3D &point, Point3D center, const CalculatedAngles &angles) {
    point = vector3DSub(point, center);
    
    point = rotatePointX(point, angles.sinx, angles.cosx);
    point = rotatePointY(point, angles.siny, angles.cosy);
    point = rotatePointZ(point, angles.sinz, angles.cosz);

    point = vector3DAdd(point, center);
}

static void calculateAngles(CalculatedAngles &angles, Vector3D eulerAngles) {
    angles.sinx = sin(eulerAngles.x);
    angles.cosx = cos(eulerAngles.x);
    angles.siny = sin(eulerAngles.y);
    angles.cosy = cos(eulerAngles.y);
    angles.sinz = sin(eulerAngles.z);
    angles.cosz = cos(eulerAngles.z);
}

static Exit rotateEveryPoint(VectorPoint3D &points, Point3D center, Vector3D eulerAngles) {
    Exit ec = points.arr ? Exit::success : Exit::modelUnininialized;

    if (isOk(ec)) {
        CalculatedAngles angles;
        calculateAngles(angles, eulerAngles);

        for (size_t i = 0; i < points.size; i++)
            rotatePoint(points.arr[i], center, angles);
    }

    return ec;
}

Exit modelRotate(Model3D &model, Vector3D eulerAngles) {
    return rotateEveryPoint(model.points, model.center, eulerAngles);
}

static void scalePoint(Point3D &point, Point3D center, Vector3D scaleVector) {
    vector3DSub(point, center);

    point.x = center.x + (point.x - center.x) * scaleVector.x;
    point.y = center.y + (point.y - center.y) * scaleVector.y;
    point.z = center.z + (point.z - center.z) * scaleVector.z;

    vector3DAdd(point, center);
}

static Exit scaleEveryPoint(VectorPoint3D &points, Point3D center, Vector3D scaleVector) {
    Exit ec = Exit::success;

    if (!points.arr) {
        ec = Exit::modelUnininialized;
    }
    else if (isZero(scaleVector.x) || isZero(scaleVector.y) || isZero(scaleVector.z)) {
        ec = Exit::modelScaleZero;
    }
    else {
        for (size_t i = 0; i < points.size; i++)
            scalePoint(points.arr[i], center, scaleVector);
    }

    return ec;
}

Exit modelScale(Model3D &model, Vector3D scaleVector) {
    return scaleEveryPoint(model.points, model.center, scaleVector);
}

Exit validatePoint(size_t vertexAmount, const Polygon polygon) {
    Exit ec = polygon.vertexIndexArray ? Exit::success : Exit::modelUnininialized;

    for (size_t i = 0; isOk(ec) && i < polygon.verticiesAmount; i++) {
        const size_t& idx = polygon.vertexIndexArray[i];
        ec = idx < vertexAmount ? Exit::success : Exit::modelInvalidVertexId;
    }

    return ec;
}

static Exit facesArrayValidate(const VectorPoint3D &points, const VectorPolygon &faces) {
    Exit ec = (points.arr && faces.arr) ? Exit::success : Exit::modelUnininialized;

    for (size_t i = 0; isOk(ec) && i < faces.size; i++) {
        ec = validatePoint(points.size, faces.arr[i]);
    }

    return ec;
}

Exit modelValidate(const Model3D &model) {
    return facesArrayValidate(model.points, model.faces);
}

static Exit projectionCopyFaces(Projection &projection, const VectorPolygon& faces) {
    Exit ec = faces.arr ? Exit::success : Exit::modelUnininialized;

    if (isOk(ec)) {
        projection.polygonArray = (Polygon *)malloc(faces.size * sizeof(Polygon));
        ec = projection.polygonArray ? Exit::success : Exit::noMemory;
    }

    int i = 0;
    while (isOk(ec) && i < int(faces.size)) {
        ec = polygonCopy(projection.polygonArray[i], faces.arr[i]);
        i++;
    }

    if (isOk(ec)) {
        projection.polygonAmount = faces.size;
    }
    else {
        i -= 2;
        while (i >= 0) {
            polygonFree(projection.polygonArray[i]);
            i--;
        }
    }

    return ec;
}

static Exit projectionCopyPoints(Projection &projection, const VectorPoint3D points) {
    Exit ec = points.arr ? Exit::success : Exit::modelUnininialized;

    if (isOk(ec)) {
        projection.pointArray = (Point2D *)malloc(points.size * sizeof(Point2D));
        ec = projection.pointArray ? Exit::success : Exit::noMemory;
    }

    if (isOk(ec)) {
        projection.pointsAmount = points.size;
        for (size_t i = 0; i < points.size; i++) {
            projection.pointArray[i] = point2DFrom3D(points.arr[i]);
            pointToScreenCoords(projection.pointArray[i]);
        }
    }

    return ec;
}

Exit modelProjectOrthogonal(Projection &projection, const Model3D &model) {
    Exit ec = Exit::success;

    projection = projectionEmpty();

    if (isOk(ec))
        ec = projectionCopyFaces(projection, model.faces);

    if (isOk(ec))
        ec = projectionCopyPoints(projection, model.points);

    if (isOk(ec)) {
        projection.center = point2DFrom3D(model.center);
    }
    else {
        projectionFree(projection);
        memset(&projection, 0, sizeof(Projection));
    }

    return ec;
}

static inline bool isValidPoint(const Point3D &p, Real cameraDistance) {
    static const Real cameraPointBufferDistance = 30;
    return p.z < cameraDistance - cameraPointBufferDistance;
}

static inline Exit isPointsValid(bool &valid, const VectorPoint3D &points, Real cameraDistance) {
    Exit ec = points.arr ? Exit::success : Exit::modelUnininialized;

    if (isOk(ec)) {
        valid = true;
        for (size_t i = 0; valid && i < points.size; i++)
            valid = isValidPoint(points.arr[i], cameraDistance);
    }

    return ec;
}

static inline Exit isCameraDistanceValid(bool &valid, const Model3D &model, Real cameraDistance) {
    Exit ec = isPointsValid(valid, model.points, cameraDistance);

    if (isOk(ec) && valid) {
        valid = valid && isValidPoint(model.center, cameraDistance);
    }

    return ec;
}

static inline Point2D pointToPerspective(Point3D point, Real cameraDistance) {
    Real k = cameraDistance / (-point.z + cameraDistance);
    Point2D result = point2DFrom3D(point);
    result = point2DMultiply(result, k);
    return result;
}

static inline Exit pointsToPerspective(Projection &projection, const VectorPoint3D &points, Real cameraDistance) {
    Exit ec = points.arr ? Exit::success : Exit::modelUnininialized;

    if (isOk(ec)) {
        for (size_t i = 0; i < points.size; i++)
            projection.pointArray[i] = pointToPerspective(points.arr[i], cameraDistance);
    }

    return ec;
}

Exit modelProjectPerspective(Projection &projection, const Model3D &model, Real cameraDistance) {
    bool valid;
    Exit ec = isCameraDistanceValid(valid, model, cameraDistance);

    if (isOk(ec)) {
        if (!valid)
            ec = Exit::inputCameraTooClose;
        else
            ec = modelProjectOrthogonal(projection, model);
    }

    if (isOk(ec))
        ec = pointsToPerspective(projection, model.points, cameraDistance);

    if (isOk(ec))
        projection.center = pointToPerspective(model.center, cameraDistance);

    return ec;
}
