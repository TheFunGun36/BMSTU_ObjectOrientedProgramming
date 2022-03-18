#include "ModelFile.hpp"
#include "Vector.hpp"
#include "String.hpp"
#include "Point.hpp"

static const Char prefixVertex[] = TEXT("v");
static const Char prefixFace[] = TEXT("f");

static Exit fileReadLine(String *&line, FILE *f) {
    const size_t bufSize = 32;
    Exit ec = strInitialize(line, TEXT(""));
    bool endl = false;

    while (isOk(ec) && !endl) {
        Char buf[bufSize];

        if (fgetws(buf, bufSize, f))
            ec = strAppend(line, buf);
        else
            ec = feof(f) ? Exit::fileEOF : Exit::fileOpenReadFail;

        if (isOk(ec))
            ec = strIsEndl(endl, line);
    }

    return ec;
}

static Exit parsePoint(Point3D &point, const String *line) {
    Exit ec = line ? Exit::success : Exit::strUninitialized;

    bool isValidCmd = false;
    if (isOk(ec)) ec =
        strIsFirstWord(isValidCmd, line, prefixVertex);

    if (isOk(ec) && !isValidCmd)
        ec = Exit::cmdInvalid;

    String *str = nullptr;
    if (isOk(ec)) ec = strDuplicate(str, line);
    if (isOk(ec)) ec = strNextNumber(str, point.x);
    if (isOk(ec)) ec = strNextNumber(str, point.y);
    if (isOk(ec)) ec = strNextNumber(str, point.z);

    strFree(str);

    return ec;
}

static void vectorToPolygon(Polygon &polygon, const VectorInt &vector) {
    polygon.verticiesAmount = vector.size;
    for (int i = 0; i < vector.size; i++)
        polygon.vertexIndexArray[i] = vector.arr[i];
}

static Exit parseFace(Polygon &face, const String *line) {
    Exit ec = line ? Exit::success : Exit::strUninitialized;

    bool isValidCmd = false;
    if (isOk(ec))
        ec = strIsFirstWord(isValidCmd, line, prefixFace);

    if (isOk(ec) && !isValidCmd)
        ec = Exit::cmdInvalid;

    String *str = nullptr;
    if (isOk(ec))
        ec = strDuplicate(str, line);

    VectorInt vertex = { 0 };

    while (isOk(ec)) {
        int number = 0;
        if (isOk(ec))
            ec = strNextNumber(str, number);

        if (isOk(ec) && number < 1)
            ec = Exit::fileOpenReadFail;

        if (isOk(ec))
            ec = vectorPushBack(vertex, number - 1);
    }

    if (ec == Exit::strEmpty)
        ec = Exit::success;

    if (isOk(ec) && vertex.size < 3)
        ec = Exit::fileOpenReadFail;

    if (isOk(ec)) ec = polygonCreate(face, vertex.size);
    if (isOk(ec)) vectorToPolygon(face, vertex);

    vectorFree(vertex);
    strFree(str);

    return ec;
}

static Exit fileOpen(FILE *&file, const Char *filename) {
    Exit ec = Exit::success;
    file = _wfopen(filename, TEXT("rt"));

    if (!file)
        ec = Exit::fileOpenReadFail;

    return ec;
}

static Exit modelLoad(Model3D &model, FILE *file) {
    Exit ec = file ? Exit::success : Exit::fileOpenReadFail;

    while (isOk(ec)) {
        String *line = nullptr;
        if (isOk(ec)) {
            ec = fileReadLine(line, file);
            if (isOk(ec)) ec = strCutUntil(line, '#');
            if (isOk(ec)) ec = strTrim(line);
        }

        if (isOk(ec)) {
            Point3D p;
            ec = parsePoint(p, line);
            if (isOk(ec)) ec = modelAddVertex(model, p);
        }

        if (ec == Exit::cmdInvalid) {
            Polygon p = { 0 };
            ec = parseFace(p, line);
            if (isOk(ec)) ec = modelAddFace(model, p);
        }

        // Не будем выбрасывать из-за неизвестных команд,
        // дабы максимизировать совместимость
        if (ec == Exit::cmdInvalid)
            ec = Exit::success;

        strFree(line);
    }

    if (ec == Exit::fileEOF)
        ec = Exit::success;
    else if (!isOk(ec))
        modelClear(model);

    return ec;
}

Exit fileModelLoad(Model3D &model, const Char *filename) {
    Exit ec = filename ? Exit::success : Exit::fileOpenReadFail;

    FILE *file = nullptr;
    if (isOk(ec))
        ec = fileOpen(file, filename);

    Model3D modelTmp = modelEmpty();

    if (isOk(ec))
        ec = modelLoad(modelTmp, file);

    if (ec == Exit::fileEOF)
        ec = Exit::success;

    if (isOk(ec)) {
        modelClear(model);
        model = modelTmp;
    }

    return ec;
}
