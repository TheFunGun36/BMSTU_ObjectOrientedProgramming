#include "FileParse.h"
#include <qfile.h>
#include <qstring.h>
#include <qtextstream.h>
#include <qregularexpression.h>

namespace wireframe {
    const static QVector<QString> skippedCommands = {
        "vt",
        "vp",
        "vn",
        "s",
        "g",
        "o",
        "mtllib",
        "usemtl",
        "#"
    };

    ExitCode objRemoveUnnecessary(QStringList &fileContent, int &lineFailed, QFile &file);
    bool objIsValidCommand(bool &skip, const QString &line);

    ExitCode objReadVerticies(QVector<Vertex3D> &vertex, int &lineFailed, const QStringList &fileContent);
    ExitCode objReadVertex(Vertex3D &vertex, const QString &string);

    ExitCode objReadFaces(Model3D &model, int &lineFailed, const QStringList &fileContent);
    ExitCode objReadFace(Surface3Dindex &face, const QString &string, int verticiesAmount);

    ExitCode objParse(Model3D &model, int &lineFailed, const QString &filename) {
        ExitCode exitCode = ExitCode::ok;
        lineFailed = 0;

        // Открыть файл
        QFile file(filename);

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            exitCode = ExitCode::fileNotOpened;
        }

        QStringList fileContent;
        if (exitCode == ExitCode::ok)
            exitCode = objRemoveUnnecessary(fileContent, lineFailed, file);

        if (exitCode == ExitCode::ok)
            exitCode = objReadVerticies(model.vertex, lineFailed, fileContent);

        if (exitCode == ExitCode::ok)
            exitCode = objReadFaces(model, lineFailed, fileContent);

        if (file.isOpen())
            file.close();

        return exitCode;
    }

    ExitCode objRemoveUnnecessary(QStringList &fileContent, int &lineFailed, QFile &file) {
        ExitCode exitCode = ExitCode::ok;
        QTextStream inputStream(&file);
        lineFailed = -1;
        fileContent.clear();
        int currentLine = 1;

        while (exitCode == ExitCode::ok && !inputStream.atEnd()) {
            QString line = inputStream.readLine().trimmed();
            bool shouldSkip;

            if (objIsValidCommand(shouldSkip, line)) {
                if (!shouldSkip) {
                    line = line.split("#")[0];
                    fileContent.push_back(line);
                }
            }
            else {
                lineFailed = currentLine;
                exitCode = ExitCode::fileInvalidCommand;
            }

            currentLine++;
        }

        return exitCode;
    }

    bool objIsValidCommand(bool &skip, const QString &line) {
        bool succeed = true;

        if (!line.size()) {
            skip = true;
        }
        else {
            succeed = line.startsWith("v ") || line.startsWith("f ");
            if (!succeed)
                succeed = line.startsWith("v\t") || line.startsWith("f\t");

            if (succeed) {
                skip = false;
            }
            else {
                skip = true;
                auto i = skippedCommands.begin();
                while (!succeed && i != skippedCommands.end()) {
                    succeed = line.startsWith(*i);
                    i++;
                }
            }
        }

        return succeed;
    }

    ExitCode objReadVerticies(QVector<Vertex3D> &vertex, int &lineFailed, const QStringList &fileContent) {
        ExitCode exitCode = ExitCode::ok;
        vertex.clear();
        vertex.reserve(fileContent.size() / 3);
        lineFailed = -1;

        int currentLine = 0;

        auto i = fileContent.constBegin();
        while (exitCode == ExitCode::ok && i != fileContent.constEnd()) {
            if (i->startsWith("v")) {
                Vertex3D v;
                exitCode = objReadVertex(v, *i);

                if (exitCode == ExitCode::ok) {
                    vertex.push_back(v);
                }
                else {
                    lineFailed = currentLine;
                    exitCode = ExitCode::fileInvalidVertex;
                    vertex.clear();
                }
            }
            i++;
            currentLine++;
        }

        return exitCode;
    }

    ExitCode objReadVertex(Vertex3D &vertex, const QString &string) {
        QString str(string);
        str.remove(0, 1);
        QStringList numbers = str.split(QRegularExpression("[ \t]"), Qt::SkipEmptyParts);

        bool success = numbers.size() >= 3;
        if (success)
            vertex.x = numbers[0].toDouble(&success);
        if (success)
            vertex.y = numbers[1].toDouble(&success);
        if (success)
            vertex.z = numbers[2].toDouble(&success);

        return success ? ExitCode::ok : ExitCode::fileInvalidVertex;
    }

    ExitCode objReadFaces(Model3D &model, int &lineFailed, const QStringList &fileContent) {
        ExitCode exitCode = ExitCode::ok;
        model.face.clear();
        lineFailed = -1;

        int currentLine = 1;

        auto i = fileContent.constBegin();
        while (exitCode == ExitCode::ok && i != fileContent.constEnd()) {
            if (i->startsWith("f")) {
                Surface3Dindex s;
                exitCode = objReadFace(s, *i, model.vertex.size());

                if (exitCode == ExitCode::ok) {
                    model.face.push_back(s);
                }
                else {
                    lineFailed = currentLine;
                    exitCode = ExitCode::fileInvalidFace;
                    model.face.clear();
                }
            }
            i++;
            currentLine++;
        }

        return exitCode;
    }

    ExitCode objReadFace(Surface3Dindex &face, const QString &string, int verticiesAmount) {
        QString str(string);
        str.remove(0, 1);
        QStringList vertexIndexes = str.split(QRegularExpression("[ \t]"), Qt::SkipEmptyParts);

        face.vertexIdx.clear();

        bool success = vertexIndexes.size() >= 3;
        if (success)
            face.vertexIdx.reserve(vertexIndexes.size());

        auto i = vertexIndexes.begin();
        while (success && i != vertexIndexes.end()) {
            QStringList slashes = i->split("/", Qt::SkipEmptyParts);
            int val;

            if (!slashes.size()) {
                success = false;
            }
            else {
                val = slashes[0].toInt(&success) - 1;
                success = val >= 0 && val < verticiesAmount;
            }

            if (success)
                face.vertexIdx.push_back(val);
            else
                face.vertexIdx.clear();

            i++;
        }

        return success ? ExitCode::ok : ExitCode::fileInvalidFace;
    }
}
