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

        model->center.x += moveVector.x;
        model->center.y += moveVector.y;
        model->center.z += moveVector.z;
    }

    return ec;
}

Exit modelRotate(Model3D *model, Vector3D eulerAngles, bool reverse) {
    Exit ec = Exit::success;

    if (!model) {
        ec = Exit::modelUnininialized;
    }
    else {
        Real sinx = sin(eulerAngles.x);
        Real cosx = cos(eulerAngles.x);
        Real siny = sin(eulerAngles.y);
        Real cosy = cos(eulerAngles.y);
        Real sinz = sin(eulerAngles.z);
        Real cosz = cos(eulerAngles.z);

        if (reverse) {
            // ROTATE Z
            for (int i = 0; i < model->points.size; i++) {
                Point3D &p = model->points.arr[i];
                Point3D &c = model->center;
                Real dx = p.x - c.x;
                Real dy = p.y - c.y;
                p.x = c.x + dx * cosz + dy * sinz;
                p.y = c.y - dx * sinz + dy * cosz;
            }
        }
        else {
            // ROTATE X
            for (int i = 0; i < model->points.size; i++) {
                Point3D &p = model->points.arr[i];
                Point3D &c = model->center;
                Real dy = p.y - c.y;
                Real dz = p.z - c.z;
                p.y = c.y + dy * cosx + dz * sinx;
                p.z = c.z - dy * sinx + dz * cosx;
            }
        }

        // ROTATE Y
        for (int i = 0; i < model->points.size; i++) {
            Point3D &p = model->points.arr[i];
            Point3D &c = model->center;
            Real dx = p.x - c.x;
            Real dz = p.z - c.z;
            p.x = c.x + dx * cosy + dz * siny;
            p.z = c.z - dx * siny + dz * cosy;
        }

        if (reverse) {
            // ROTATE X
            for (int i = 0; i < model->points.size; i++) {
                Point3D &p = model->points.arr[i];
                Point3D &c = model->center;
                Real dy = p.y - c.y;
                Real dz = p.z - c.z;
                p.y = c.y + dy * cosx + dz * sinx;
                p.z = c.z - dy * sinx + dz * cosx;
            }
        }
        else {
            //ROTATE Z
            for (int i = 0; i < model->points.size; i++) {
                Point3D &p = model->points.arr[i];
                Point3D &c = model->center;
                Real dx = p.x - c.x;
                Real dy = p.y - c.y;
                p.x = c.x + dx * cosz + dy * sinz;
                p.y = c.y - dx * sinz + dy * cosz;
            }
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

Exit modelProjectOrthogonal(Projection &projection, const Model3D *model) {
    Exit ec = model ? Exit::success : Exit::modelUnininialized;

    if (isOk(ec))
        ec = allocImpl(projection.pointArray, model->points.size);
    if (isOk(ec))
        ec = allocImpl(projection.polygonArray, model->faces.size);

    if (isOk(ec)) {
        size_t pointsAmount = model->points.size;
        size_t facesAmount = model->faces.size;
        int i = 0;
        while (isOk(ec) && i < facesAmount) {
            Polygon *dst = projection.polygonArray + i;
            Polygon *src = model->faces.arr + i;

            ec = allocImpl(dst->vertexIndexArray, src->amount);
            i++;
        }

        if (!isOk(ec)) {
            i -= 2;
            while (i > 0) {
                free(projection.polygonArray[i].vertexIndexArray);
                i--;
            }
        }
        else {
            for (int i = 0; i < pointsAmount; i++) {
                projection.pointArray[i].x = model->points.arr[i].x;
                projection.pointArray[i].y = -model->points.arr[i].y;
            }

            projection.pointsAmount = pointsAmount;
            projection.polygonAmount = facesAmount;

            for (int i = 0; i < facesAmount; i++) {
                for (int j = 0; j < model->faces.arr[i].amount; j++)
                    projection.polygonArray[i].vertexIndexArray[j] = model->faces.arr[i].vertexIndexArray[j];
                projection.polygonArray[i].amount = model->faces.arr[i].amount;
            }

            projection.center.x = model->center.x;
            projection.center.y = model->center.y;
        }
    }

    if (!isOk(ec))
        projectionFree(projection);

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
