#include "Projection.hpp"

Exit polygonCreate(Polygon &p, size_t size) {
    Exit ec = size > 0 ? Exit::success : Exit::sizeInvalid;
    
    if (isOk(ec)) {
        p.vertexIndexArray = (size_t *)malloc(size * sizeof(Polygon));
        ec = p.vertexIndexArray ? Exit::success : Exit::noMemory;
    }

    if (isOk(ec))
        p.amount = size;

    return ec;
}

void polygonFree(Polygon &p) {
    free(p.vertexIndexArray);
    memset(&p, 0, sizeof(Polygon));
}

void projectionFree(Projection &p) {
    free(p.pointArray);
    for (int i = 0; i < p.polygonAmount; i++)
        polygonFree(p.polygonArray[i]);
    free(p.polygonArray);
    memset(&p, 0, sizeof(Projection));
}
