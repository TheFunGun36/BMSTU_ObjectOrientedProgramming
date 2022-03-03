#pragma once
#include <qstring.h>
#include "Model3D.h"

namespace file {
    struct ErrorParse {
        enum Type {
            noError,
            fileNotOpened,
            invalidCommand,
            invalidVertex,
            invalidFace
        };

        Type type;
        int line;
        QString filename;
    };

    bool objParse(Model3D &model, ErrorParse &error, const QString &filename);
    QString getErrorMessage(const ErrorParse &error);
}
