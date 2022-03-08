#include "Model3D.hpp"
#include <cassert>
#include <cmath>
#include "Vector.hpp"
#include "MemoryImpl.hpp"

struct Model3D {
    Vector<Point3D> points;
    Vector<Polygon> faces;
    Point3D center;
};

Exit modelInitialize(Model3D *&model) {
    Exit ec = Exit::success;

    if (model)
        ec = Exit::modelInitialized;
    else
        ec = allocImpl(model);

    if (isOk(ec))
        zeroMemory(model);

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
        zeroMemory(&face);

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
    }

    return ec;
}

Exit modelRotate(Model3D *model, Vector3D eulerAngles) {
    Exit ec = Exit::success;

    if (!model) {
        ec = Exit::modelUnininialized;
    }
    else {
        double sinx = sin(eulerAngles.x);
        double cosx = cos(eulerAngles.x);
        double siny = sin(eulerAngles.y);
        double cosy = cos(eulerAngles.y);
        double sinz = sin(eulerAngles.z);
        double cosz = cos(eulerAngles.z);

        for (int i = 0; i < model->points.size; i++) {
            Point3D &p = model->points.arr[i];
            Point3D &c = model->center;
            double dx = p.x - c.x;
            double dy = p.y - c.y;
            double dz = p.z - c.z;

            p.y = c.y + dy * cosx + dz * sinx;
            p.z = c.z - dy * sinx + dz * cosx;
            p.x = c.x + dx * cosy + dz * siny;
            p.z = c.z - dx * siny + dz * cosy;
            p.x = c.x + dx * cosz + dy * sinz;
            p.y = c.y - dx * sinz + dy * cosz;
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

Exit modelProjectOrthogonal(Projection *&projection, const Model3D *model) {
    Exit ec = model ? Exit::success : Exit::modelUnininialized;
    if (isOk(ec) && projection)
        ec = Exit::nonZeroInputPtr;

    Point2D *pointArray = nullptr;
    Polygon *faceArray = nullptr;
    if (isOk(ec))
        ec = allocImpl(pointArray, model->points.size);
    if (isOk(ec))
        ec = allocImpl(faceArray, model->faces.size);

    if (isOk(ec)) {
        int pointsAmount = model->points.size;
        int facesAmount = model->faces.size;
        int i = 0;
        while (isOk(ec) && i < facesAmount) {
            Polygon *dst = faceArray + i;
            Polygon *src = model->faces.arr + i;

            ec = allocImpl(dst->vertexIndexArray, src->amount);
            i++;
        }

        if (!isOk(ec)) {
            i -= 2;
            while (i > 0) {
                free(faceArray[i].vertexIndexArray);
                i--;
            }
        }
        else {
            for (int i = 0; i < pointsAmount; i++) {
                projection->pointArray[i].x = model->points.arr[i].x;
                projection->pointArray[i].y = -model->points.arr[i].y;
            }

            projection->pointsAmount = pointsAmount;
            projection->pointArray = pointArray;

            projection->polygonAmount = facesAmount;
            projection->polygonArray = faceArray;

            for (int i = 0; i < facesAmount; i++) {
                memcpy(faceArray[i].vertexIndexArray,
                    model->faces.arr[i].vertexIndexArray,
                    model->faces.arr[i].amount * sizeof(size_t));
                faceArray[i].amount = model->faces.arr[i].amount;
            }

            projection->center.x = model->center.x;
            projection->center.y = model->center.y;
        }
    }

    if (!isOk(ec)) {
        free(pointArray);
        free(faceArray);
    }

    return ec;
}

static inline bool isCameraDistanceValid(const Model3D &model, double cameraDistance) {
    bool valid = true;
    static const double cameraPointBufferDistance = 30;

    Point3D *p = model.points.arr;
    while (valid && p < model.points.arr + model.points.size) {
        valid = p->z < cameraDistance + cameraPointBufferDistance;
        p++;
    }

    return valid;
}

Exit modelProjectPerspective(Projection *&projection, const Model3D *model, double cameraDistance) {
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
        for (int i = 0; i < projection->pointsAmount; i++) {
            double k = cameraDistance / (model->points.arr[i].z + cameraDistance);
            projection->pointArray[i].x *= k;
            projection->pointArray[i].y *= k;
        }
    }

    return ec;
}
