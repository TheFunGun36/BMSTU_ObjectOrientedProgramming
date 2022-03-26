#include <cstdio>
#include "ModelFile.hpp"
#include "Vector.hpp"
#include "String.hpp"
#include "Point.hpp"
#include <qdebug.h>

static const Char prefixVertex[] = TEXT("v");
static const Char prefixFace[] = TEXT("f");

enum class Command {
    vertex,
    face,
    unknown
};

static Exit fileReadLine(String *&line, FILE *f) {
    const size_t bufSize = 32;
    Exit ec = strInitialize(line, TEXT(""));
    bool endl = false;

    while (isOk(ec) && !endl) {
        Char buf[bufSize];

        if (fgets(buf, bufSize, f))
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
    for (size_t i = 0; i < vector.size; i++)
        polygon.vertexIndexArray[i] = vector.arr[i];
}

static Exit parseFace(Polygon &face, const String *line) {
    Exit ec = line ? Exit::success : Exit::strUninitialized;

    bool isValidCmd = false;
    face = { 0 };

    if (isOk(ec))
        ec = strIsFirstWord(isValidCmd, line, prefixFace);

    if (isOk(ec) && !isValidCmd)
        ec = Exit::cmdInvalid;

    String *str = nullptr;
    if (isOk(ec))
        ec = strDuplicate(str, line);

    VectorInt vertex = { 0, 0, nullptr };

    while (isOk(ec)) {
        int number = 0;
        if (isOk(ec))
            ec = strNextNumber(str, number);

        if (isOk(ec) && number < 1)
            ec = Exit::modelInvalidVertexId;

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
    file = fopen(filename, TEXT("rt"));

    if (!file)
        ec = Exit::fileOpenReadFail;

    return ec;
}

static inline Exit fileReadCommand(String *&line, FILE *file) {
    Exit ec = fileReadLine(line, file);

    if (isOk(ec))
        ec = strCutUntil(line, '#');

    if (isOk(ec)) {
        ec = strTrim(line);
    }
    else {
        strFree(line);
        line = nullptr;
    }

    return ec;
}

static Exit determineCmd(Command &cmd, String *line) {
    Exit ec = line ? Exit::success : Exit::strUninitialized;

    bool match = false;
    if (isOk(ec)) {
        ec = strIsFirstWord(match, line, "v");
        if (match) cmd = Command::vertex;
    }

    if (isOk(ec) && !match) {
        ec = strIsFirstWord(match, line, "f");
        if (match) cmd = Command::face;
    }

    if (isOk(ec) && !match)
        cmd = Command::unknown;

    return ec;
}

static Exit appendModelElement(Model3D &model, String *element, Command cmd) {
    Exit ec = element ? Exit::success : Exit::strUninitialized;
    
    if (!isOk(ec))
        return ec;

    switch (cmd) {
        case Command::vertex: {
            Point3D p;
            ec = parsePoint(p, element);
            if (isOk(ec)) ec = modelAddVertex(model, p);
            break;
        }
        case Command::face: {
            Polygon p;
            ec = parseFace(p, element);
            if (isOk(ec)) ec = modelAddFace(model, p);
            break;
        }
        default:
            ec = Exit::success;
    }

    return ec;
}

static Exit modelLoad(Model3D &model, FILE *file) {
    Exit ec = file ? Exit::success : Exit::fileOpenReadFail;

    bool eofReached = false;
    while (isOk(ec) && !eofReached) {
        String *line = nullptr;
        ec = fileReadCommand(line, file);

        Command cmd;
        if (isOk(ec))
            ec = determineCmd(cmd, line);

        if (isOk(ec))
            ec = appendModelElement(model, line, cmd); //TODO!

        strFree(line);

        if (ec == Exit::fileEOF) {
            eofReached = true;
            ec = Exit::success;
        }
    }
    
    if (!isOk(ec))
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

    if (isOk(ec)) {
        ec = modelValidate(modelTmp);
        if (!isOk(ec))
            modelClear(modelTmp);
    }

    if (isOk(ec)) {
        modelClear(model);
        model = modelTmp;
    }

    return ec;
}
