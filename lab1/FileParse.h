#pragma once
#include <qstring.h>
#include "Model3D.h"
#include "ProcessEntry.h"

namespace wireframe {
    ExitCode objParse(Model3D &model, int &lineFailed, const QString &filename);
    QString getErrorMessage(ExitCode error, int lineFailed = -1);
}
