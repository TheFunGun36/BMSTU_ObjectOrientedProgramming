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
        fileInvalidFace,
        fileNotCreated
    };

    struct UserData {
        QString filename;
        Model3D model;
        QVector3D moveVector;
        QVector3D scalePoint;
        QVector3D scaleCoeficients;
        QVector3D rotatePoint;
        QVector3D rotateAngles;
        qreal cameraDistance;
        int fileLineFailed;
        bool isPerspective;
    };

    ExitCode processEntry(UserData &ud, Command cmd);
    QString getErrorMessage(ExitCode error, int lineFailed);
}
