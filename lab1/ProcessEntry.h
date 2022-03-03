#pragma once
#include <qstring.h>
#include <qvector3d.h>
#include "Model3D.h"

namespace wireframe {
    enum class Command {
        fileLoad,
        fileSave,
        modelMove,
        modelScale,
        modelRotate
    };

    enum class ExitCode {
        ok,
        cmdInvalid,
        fileNotOpened,
        fileInvalidCommand,
        fileInvalidVertex,
        fileInvalidFace
    };

    struct UserData {
        QString filename;
        Model3D model;
        QVector3D moveVector;
        QVector3D scalePoint;
        QVector3D scaleCoefficients;
        QVector3D rotatePoint;
        QVector3D rotateAngles;
        int fileLineFailed;
    };

    ExitCode processEntry(Command cmd, UserData ud);
    QString getErrorMessage(ExitCode error, int lineFailed);
}
