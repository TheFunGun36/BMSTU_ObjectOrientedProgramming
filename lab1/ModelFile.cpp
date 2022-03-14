#include "ModelFile.hpp"
#include "Vector.hpp"
#include "String.hpp"
#include "Point.hpp"

#define SET_EC_IF_OK(call) if (isOk(ec)) ec = (call)

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

        SET_EC_IF_OK(strIsEndl(endl, line));
    }

    return ec;
}

static Exit parsePoint(Point3D &point, const String *line) {
    Exit ec = line ? Exit::success : Exit::strUninitialized;

    bool isValidCmd = false;
    SET_EC_IF_OK(strIsFirstWord(isValidCmd, line, prefixVertex));

    if (isOk(ec) && !isValidCmd)
        ec = Exit::cmdInvalid;

    String *str = nullptr;
    SET_EC_IF_OK(strDuplicate(str, line));

    SET_EC_IF_OK(strNextWord(str));
    SET_EC_IF_OK(strToNumber(point.x, str));
    SET_EC_IF_OK(strNextWord(str));
    SET_EC_IF_OK(strToNumber(point.y, str));
    SET_EC_IF_OK(strNextWord(str));
    SET_EC_IF_OK(strToNumber(point.z, str));

    strFree(str);

    return ec;
}

static void vectorToPolygon(Polygon &polygon, const VectorInt &vector) {
    polygon.amount = vector.size;
    for (int i = 0; i < vector.size; i++)
        polygon.vertexIndexArray[i] = vector.arr[i];
}

static Exit parseFace(Polygon &face, const String *line) {
    Exit ec = line ? Exit::success : Exit::strUninitialized;

    bool isValidCmd = false;
    SET_EC_IF_OK(strIsFirstWord(isValidCmd, line, prefixFace));

    if (isOk(ec) && !isValidCmd)
        ec = Exit::cmdInvalid;

    String *str = nullptr;
    SET_EC_IF_OK(strDuplicate(str, line));

    bool isEmpty = false;

    VectorInt vertex = { 0 };

    while (isOk(ec) && !isEmpty) {
        int number = 0;
        SET_EC_IF_OK(strNextWord(str));
        SET_EC_IF_OK(strIsEmpty(isEmpty, str));

        if (!isEmpty) {
            SET_EC_IF_OK(strToNumber(number, str));

            if (isOk(ec) && number < 1)
                ec = Exit::fileOpenReadFail;

            SET_EC_IF_OK(vectorPushBack(vertex, number - 1));
        }
    }

    if (isOk(ec) && vertex.size < 3)
        ec = Exit::fileOpenReadFail;

    SET_EC_IF_OK(polygonCreate(face, vertex.size));

    if (isOk(ec))
        vectorToPolygon(face, vertex);

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

static Exit fileParseLine(FILE *file, Model3D *model) {
    Exit ec = (file && model) ? Exit::success : Exit::modelUnininialized;

    String *line = nullptr;
    if (isOk(ec)) {
        ec = fileReadLine(line, file);
        SET_EC_IF_OK(strCutUntil(line, '#'));
        SET_EC_IF_OK(strTrim(line));
    }

    if (isOk(ec)) {
        Point3D p;
        ec = parsePoint(p, line);
        SET_EC_IF_OK(modelAddVertex(model, p));
    }

    if (ec == Exit::cmdInvalid) {
        Polygon p = { 0 };
        ec = parseFace(p, line);
        SET_EC_IF_OK(modelAddFace(model, p));
    }

    strFree(line);
    return ec;
}

Exit fileModelLoad(Model3D *&model, const Char *filename) {
    Exit ec = model ? Exit::success : Exit::modelUnininialized;

    FILE *file = nullptr;
    SET_EC_IF_OK(fileOpen(file, filename));

    Model3D *modelTmp = nullptr;
    SET_EC_IF_OK(modelInitialize(modelTmp));

    while (isOk(ec)) {
        ec = fileParseLine(file, modelTmp);

        // Не будем выбрасывать из-за неизвестных команд,
        // дабы максимизировать совместимость
        if (ec == Exit::cmdInvalid)
            ec = Exit::success;
    }

    if (ec == Exit::fileEOF)
        ec = Exit::success;

    if (!isOk(ec)) {
        modelFree(modelTmp);
    }
    else {
        modelFree(model);
        model = modelTmp;
    }

    return ec;
}
