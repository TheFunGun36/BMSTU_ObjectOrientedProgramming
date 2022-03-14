#include "Projection.h"

Exit polygonCreate(Polygon &p, size_t verticiesAmount) {
    Exit ec = verticiesAmount > 0 ? Exit::success : Exit::sizeInvalid;

    if (isOk(ec)) {
        p.vertexIndexArray = (size_t *)malloc(verticiesAmount * sizeof(Polygon));
        ec = p.vertexIndexArray ? Exit::success : Exit::noMemory;
    }

    if (isOk(ec))
        p.verticiesAmount = verticiesAmount;

    return ec;
}

void polygonFree(Polygon &p) {
    free(p.vertexIndexArray);
    memset(&p, 0, sizeof(Polygon));
}

Exit polygonCopy(Polygon &dst, const Polygon &src) {
    Exit ec = polygonCreate(dst, src.verticiesAmount);

    if (isOk(ec)) {
        memcpy(dst.vertexIndexArray, src.vertexIndexArray, src.verticiesAmount * sizeof(size_t));
        dst.verticiesAmount = src.verticiesAmount;
    }

    return ec;
}

void projectionFree(Projection &p) {
    free(p.pointArray);
    for (int i = 0; i < p.polygonAmount; i++)
        polygonFree(p.polygonArray[i]);
    free(p.polygonArray);
    memset(&p, 0, sizeof(Projection));
}
