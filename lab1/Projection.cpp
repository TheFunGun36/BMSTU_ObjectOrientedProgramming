#include "Projection.hpp"
#include "MemoryImpl.hpp"

Exit polygonCreate(Polygon &p, size_t size) {
    Exit ec = size > 0 ? Exit::success : Exit::sizeInvalid;
    
    if (isOk(ec))
        ec = allocImpl(p.vertexIndexArray, size);

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
    for (int i = 0; i < p.pointsAmount; i++)
        polygonFree(p.polygonArray[i]);
    free(p.polygonArray);
    zeroMemory(&p);
}
