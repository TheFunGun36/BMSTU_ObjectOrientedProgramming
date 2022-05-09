#include "ModelFile.hpp"
#include <cstdio>
#include <cstring>
#include <cctype>
#include "Vector.hpp"
#include "Point.hpp"

enum class Command {
    vertex,
    face,
    unknown
};

static bool isLineComplete(IN const char *str) {
    if (!str)
        return false;

    const char *end = strchr(str, '\0');

    return (end - 1) <= str || *(end - 1) == '\n';
}

static bool stringRealloc(VAR char *&string, IN size_t newLength) {
    char *buff = (char *)realloc(string, newLength * sizeof(char));
    bool result = false;

    if (buff) {
        string = buff;
        result = true;
    }

    return result;
}

static bool stringAlloc(OUT char *&string, IN size_t length) {
    string = (char *)malloc(length + sizeof(char));
    return string;
}

static bool readFirstBlock(OUT char *&str, IN size_t size, IN FILE *f) {
    bool ok = stringAlloc(str, size);

    if (ok) {
        ok = fgets(str, size, f);

        if (!ok) {
            free(str);
            str = nullptr;
        }
    }

    return ok;
}

static bool readNextBlock(VAR char *&str, IN size_t blockSize, IN FILE *f) {
    if (!str)
        return false;

    bool ok = stringRealloc(str, strlen(str) + blockSize);

    if (ok) {
        char *end = strchr(str, '\0');
        ok = fgets(end, blockSize, f);
    }

    return ok;
}

static char *fileReadLine(IN FILE *f) {
    const size_t step = 3;
    char *str = nullptr;

    if (readFirstBlock(str, step + 1, f)) {
        while (!isLineComplete(str) && readNextBlock(str, step, f));
    }

    return str;
}

static Exit parsePoint(OUT Point3D &point, IN const char *str) {
    if (!str)
        return Exit::strUninitialized;

    point = point3DEmpty();
    Exit ec = Exit::success;

    char *endl = nullptr;
    point.x = strtod(str, &endl);

    if (str != endl) {
        str = endl;
        point.y = strtod(str, &endl);
    }

    if (str != endl) {
        str = endl;
        point.z = strtod(endl, &endl);
    }

    if (str == endl)
        ec = Exit::fileOpenReadFail;

    return ec;
}

static const char *skipToSpace(IN const char *str) {
    if (str) {
        while (!isspace(*str))
            str++;
    }
    return str;
} 

static Exit parseFaceData(OUT VectorInt &numbers, IN const char *str) {
    if (!str)
        return Exit::strUninitialized;

    Exit ec = Exit::success;
    numbers = vectorIntEmpty();

    char *endl = nullptr;
    do {
        int val = strtol(str, &endl, 10);
        if (str != endl) {
            ec = vectorPushBack(numbers, val - 1);

            if (isOk(ec)) {
                str = endl;
                str = skipToSpace(str); // need to skip /<number>/<number>, so can't use endl
            }
        }
    } while (isOk(ec) && str != endl);

    if (!isOk(ec) && numbers.arr)
        vectorFree(numbers);

    return ec;
}

static Exit parseFace(OUT Polygon &face, IN const char *line) {
    if (!line)
        return Exit::strUninitialized;

    face = polygonEmpty();
    Exit ec = Exit::success;

    VectorInt vertex;
    ec = parseFaceData(vertex, line);

    if (isOk(ec)) {
        if (vertex.size < 3) {
            ec = Exit::fileOpenReadFail;
            vectorFree(vertex);
        }
        else {
            face.verticiesAmount = vertex.size;
            face.vertexIndexArray = vertex.arr;
        }
    }

    return ec;
}

static Exit fileOpen(OUT FILE *&file, IN const char *filename) {
    Exit ec = Exit::success;
    file = fopen(filename, "rt");

    if (!file)
        ec = Exit::fileOpenReadFail;

    return ec;
}

static Command determineCmd(IN const char *str) {
    if (!str)
        return Command::unknown;

    Command cmd = Command::unknown;

    if (strlen(str) >= 2 && isspace(str[1])) {
        if (str[0] == 'v')
            cmd = Command::vertex;
        else if (str[0] == 'f')
            cmd = Command::face;
    }

    return cmd;
}

static inline const char *preprocessLine(IN const char *str) {
    if (str)
        str += 2;
    return str;
}

static Exit parseLine(OUT ModelElement &modelElement, IN const char *str) {
    if (!str)
        return Exit::strUninitialized;

    modelElement.type = ModelElementType::undefined;

    Exit ec = Exit::success;
    Command cmd = determineCmd(str);
    str = preprocessLine(str);

    if (cmd == Command::vertex) {
        Point3D p;
        ec = parsePoint(p, str);
        if (isOk(ec)) {
            modelElement.type = ModelElementType::vertex;
            modelElement.data.vertex = p;
        }
    }
    else if (cmd == Command::face) {
        Polygon p;
        ec = parseFace(p, str);
        if (isOk(ec)) {
            modelElement.type = ModelElementType::face;
            modelElement.data.polygon = p;
        }
    }

    return ec;
}

static Exit modelLoad(OUT Model3D &model, IN FILE *file) {
    Exit ec = file ? Exit::success : Exit::fileOpenReadFail;

    char *line = nullptr;
    while (isOk(ec) && (line = fileReadLine(file))) {
        ModelElement modelElement;
        ec = parseLine(modelElement, line);
        if (isOk(ec))
            ec = modelAddElement(model, modelElement);

        free(line);
    }
    
    if (!isOk(ec))
        modelClear(model);

    return ec;
}

Exit fileModelLoad(VAR Model3D &model, IN const char *filename) {
    Exit ec = filename ? Exit::success : Exit::fileOpenReadFail;

    FILE *file = nullptr;
    if (isOk(ec))
        ec = fileOpen(file, filename);

    Model3D modelTmp = modelEmpty();

    if (isOk(ec)) {
        ec = modelLoad(modelTmp, file);

        if (isOk(ec)) {
            ec = modelValidate(modelTmp);

            if (!isOk(ec))
                modelClear(modelTmp);
        }
    }

    if (isOk(ec)) {
        modelClear(model);
        model = modelTmp;
    }

    return ec;
}
