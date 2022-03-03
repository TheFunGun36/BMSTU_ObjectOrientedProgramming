#include "FileParse.h"
#include <qfile.h>
#include <qstring.h>
#include <qtextstream.h>
#include <qregularexpression.h>

namespace file {
    const QVector<QString> skippedCommands = {
        "vt",
        "vp",
        "g",
        "o",
        "mtllib",
        "usemtl",
        "#"
    };

    QString getErrorMessage(const ErrorParse &error);
    bool objParse(Model3D &model, ErrorParse &error, const QString &filename);
    bool objRemoveUnnecessary(QStringList &fileContent, ErrorParse &error, QFile &file);
    bool objIsValidCommand(bool &skip, const QString &line);

    bool objReadVerticies(QVector<Vertex3D> &vertex, ErrorParse &error, const QStringList &fileContent);
    bool objReadVertex(Vertex3D &vertex, ErrorParse &error, const QString &string);

    bool objReadFaces(QList<Surface3Dindex> &faces, ErrorParse &error, const QStringList &fileContent);
    bool objReadFace(Surface3Dindex &face, ErrorParse &error, const QString &string);

    QString getErrorMessage(const ErrorParse &error) {
        QString result = "Данные о 3D модели были успешно считаны из файла " + error.filename;

        switch (error.type) {
            case ErrorParse::fileNotOpened:
                result = "Не удалось открыть файл " + error.filename;
                break;
            case ErrorParse::invalidCommand:
                result = "В файле " + error.filename +
                    " в строке " + QString::number(error.line) +
                    " используется неизвестная команда";
                break;
        }

        return result;
    }

    bool objParse(Model3D &model, ErrorParse &error, const QString &filename) {
        bool succeed = true;
        error.filename = filename;
        error.type = ErrorParse::noError;
        error.line = 0;
        
        // Открыть файл
        QFile file(filename);

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            error.type = ErrorParse::fileNotOpened;
            succeed = false;
        }
        
        QStringList fileContent;
        if (succeed) {
            succeed = objRemoveUnnecessary(fileContent, error, file);
        }

        if (succeed) {
            succeed = objReadVerticies(model.vertex, error, fileContent);
        }

        if (succeed) {
            succeed = objReadFaces(model.face, error, fileContent);
        }

        return succeed;
    }

    bool objRemoveUnnecessary(QStringList &fileContent, ErrorParse &error, QFile &file) {
        bool succeed = true;
        QTextStream inputStream(&file);
        int currentLine = 1;

        while (succeed && !inputStream.atEnd()) {
            QString line = inputStream.readLine().trimmed();
            bool shouldSkip;

            if (objIsValidCommand(shouldSkip, line)) {
                if (!shouldSkip) {
                    line = line.split("#")[0];
                    fileContent.push_back(line);
                }
            }
            else {
                error.line = currentLine;
                error.type = ErrorParse::invalidCommand;
                succeed = false;
            }

            currentLine++;
        }

        return succeed;
    }

    bool objIsValidCommand(bool &skip, const QString &line) {
        bool succeed = true;

        if (!line.size()) {
            skip = true;
        }
        else {
            succeed = line.startsWith("v ") || line.startsWith("f ");
            
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

    bool objReadVerticies(QVector<Vertex3D> &vertex, ErrorParse &error, const QStringList &fileContent) {
        bool succeed = true;
        vertex.clear();
        vertex.reserve(fileContent.size() / 3);

        int currentLine = 0;

        auto i = fileContent.constBegin();
        while (succeed && i != fileContent.constEnd()) {
            if (i->startsWith("v")) {
                Vertex3D v;
                succeed = objReadVertex(v, error, *i);

                if (succeed) {
                    vertex.push_back(v);
                }
                else {
                    error.line = currentLine;
                    error.type = ErrorParse::invalidVertex;
                    vertex.clear();
                }
            }
            i++;
            currentLine++;
        }

        return succeed;
    }

    bool objReadVertex(Vertex3D &vertex, ErrorParse &error, const QString &string) {
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

        return success;
    }

    bool objReadFaces(QList<Surface3Dindex> &faces, ErrorParse &error, const QStringList &fileContent) {
        bool succeed = true;
        faces.clear();

        int currentLine = 1;

        auto i = fileContent.constBegin();
        while (succeed && i != fileContent.constEnd()) {
            if (i->startsWith("f")) {
                Surface3Dindex s;
                succeed = objReadFace(s, error, *i);

                if (succeed) {
                    faces.push_back(s);
                }
                else {
                    error.line = currentLine;
                    error.type = ErrorParse::invalidFace;
                    faces.clear();
                }
            }
            i++;
            currentLine++;
        }

        return succeed;
    }

    bool objReadFace(Surface3Dindex &face, ErrorParse &error, const QString &string) {
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

            if (!slashes.size())
                success = false;
            else
                val = slashes[0].toInt(&success) - 1;

            if (success)
                face.vertexIdx.push_back(val);
            else
                face.vertexIdx.clear();

            i++;
        }

        return success;
    }
}
