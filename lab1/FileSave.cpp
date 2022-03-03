#include "FileSave.h"
#include <qfile.h>
#include <qtextstream.h>

namespace wireframe {
    ExitCode objSave(const Model3D &model, const QString &filename) {
        QFile file(filename);
        ExitCode exitCode = ExitCode::ok;

        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            exitCode = ExitCode::fileNotCreated;

        if (exitCode == ExitCode::ok) {
            QTextStream fileStream(&file);

            for (const Vertex3D &v : model.vertex)
                fileStream << "v " << v.x << ' ' << v.y << ' ' << v.z << '\n';
            for (auto f : model.face) {
                fileStream << "f ";
                for (auto idx : f.vertexIdx) {
                    fileStream << idx + 1 << ' ';
                }
                fileStream << '\n';
            }
        }

        if (file.isOpen())
            file.close();

        return exitCode;
    }
}
