#include "ModelFile.hpp"
#include "Vector.hpp"
#include "String.hpp"
#include "Point.hpp"

#define SET_EC_IF_OK(call) if (isOk(ec)) ec = (call)

static const Char prefixVertex[] = "v";
static const Char prefixFace[] = "f";

static Exit fileReadLine(String *&line, FILE *f) {
    const size_t bufSize = 32;
    Exit ec = strInitialize(line, "");
    bool endl = false;

    while (isOk(ec) && !endl) {
        Char buf[bufSize];

        if (fgets(buf, bufSize, f))
            ec = strAppend(line, buf);
        else
            ec = feof(f) ? Exit::fileEOF : Exit::fileOpenReadFail;

        SET_EC_IF_OK(strIsEndl(endl, line));
    }

    return ec;
}

static Exit parsePoint(Point3D &point, const String *line) {
    Exit ec = line ? Exit::success : Exit::strUninitialized;

    bool isValidCmd;
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
    SET_EC_IF_OK(strToNumber(point.y, str));

    strFree(str);

    return ec;
}

static Exit parseFace(Polygon &face, const String *line) {
    Exit ec = line ? Exit::success : Exit::strUninitialized;

    bool isValidCmd;
    SET_EC_IF_OK(strIsFirstWord(isValidCmd, line, prefixFace));

    if (isOk(ec) && !isValidCmd)
        ec = Exit::cmdInvalid;

    String *str = nullptr;
    SET_EC_IF_OK(strDuplicate(str, line));

    bool isEmpty;
    SET_EC_IF_OK(strIsEmpty(isEmpty, str));

    Vector<size_t> vertex;
    SET_EC_IF_OK(vectorInitialize(vertex, 3));
    
    while (isOk(ec)) {
        int number;
        ec = strNextWord(str);
        SET_EC_IF_OK(strToNumber(number, str));

        if (isOk(ec) && number < 1)
            ec = Exit::fileOpenReadFail;

        SET_EC_IF_OK(vectorPushBack(vertex, static_cast<size_t>(number)));
    }

    if (isOk(ec) && vertex.size < 3)
        ec = Exit::fileOpenReadFail;

    SET_EC_IF_OK(polygonCreate(face, vertex.size));

    if (isOk(ec)) {
        face.amount = vertex.size;
        memcpy(face.vertexIndexArray, vertex.arr, vertex.size * sizeof(size_t));
    }

    vectorFree(vertex);
    strFree(str);

    return ec;
}

Exit fileModelLoad(Model3D *model, int &lineFailed, const Char *filename) {
    Exit ec = model ? Exit::success : Exit::modelUnininialized;

    FILE *file = nullptr;
    if (isOk(ec)) {
        file = fopen(filename, "rt");

        if (!file)
            ec = Exit::fileOpenReadFail;
    }

    Model3D *modelTmp = nullptr;
    SET_EC_IF_OK(modelInitialize(modelTmp));

    lineFailed = 0;
    bool eof = false;
    while (isOk(ec) && !eof) {
        lineFailed++;

        String *line = nullptr;
        ec = fileReadLine(line, file);

        if (ec == Exit::fileEOF) {
            eof = true;
            ec = Exit::success;
        }

        SET_EC_IF_OK(strCutUntil(line, '#'));
        SET_EC_IF_OK(strTrim(line));

        if (isOk(ec)) {
            Point3D p;
            ec = parsePoint(p, line);

            SET_EC_IF_OK(modelAddVertex(modelTmp, p));
        }

        if (ec == Exit::cmdInvalid) {
            Polygon p;
            ec = parseFace(p, line);

            SET_EC_IF_OK(modelAddFace(modelTmp, p));
            polygonFree(p);
        }

        // Не будем выбрасывать из-за неизвестных команд,
        // дабы максимизировать совместимость
        if (ec == Exit::cmdInvalid)
            ec = Exit::success;

        strFree(line);
    }

    if (isOk(ec)) {
        modelFree(model);
        model = modelTmp;
        lineFailed = -1;
    }
    else {
        modelFree(modelTmp);
    }

    return ec;
}

Exit fileModelSave(const Model3D *model, const Char *filename) {
    throw "TODO";
    return Exit();
}
