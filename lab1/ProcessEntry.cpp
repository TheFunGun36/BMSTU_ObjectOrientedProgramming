#include "ProcessEntry.h"
#include "FileParse.h"
#include "FileSave.h"

namespace wireframe {
    ExitCode processEntry(UserData &ud, Command cmd) {
        ExitCode exitCode = ExitCode::ok;
        switch (cmd) {
            case Command::fileLoad:
                exitCode = objParse(ud.model, ud.fileLineFailed, ud.filename);
                break;
            case Command::fileSave:
                exitCode = objSave(ud.model, ud.filename);
                break;
            case Command::modelMove:
                modelMove(ud.model, ud.moveVector);
                break;
            case Command::modelRotate:
                modelRotate(ud.model, ud.rotatePoint, ud.rotateAngles);
                break;
            case Command::modelScale:
                modelScale(ud.model, ud.scalePoint, ud.scaleCoeficients);
                break;
            default:
                exitCode = ExitCode::cmdInvalid;
        }

        return exitCode;
    }

    QString getErrorMessage(ExitCode error, int lineFailed) {
        QString result = "Данные о 3D модели были успешно считаны из файла";

        switch (error) {
            case ExitCode::fileNotOpened:
                result = "Не удалось открыть файл";
                break;
            case ExitCode::fileInvalidCommand:
                result = "В строке " + QString::number(lineFailed) + " используется неизвестная команда";
                break;
            case ExitCode::fileInvalidVertex:
                result = "В строке " + QString::number(lineFailed) + " вершина задана некорректно";
                break;
            case ExitCode::fileInvalidFace:
                result = "В строке " + QString::number(lineFailed) + " полигон задан некорректно";
                break;
            case ExitCode::cmdInvalid:
                result = "В программу была подана неизвестная команда";
                break;
            case ExitCode::fileNotCreated:
                result = "Не удалось создать файл";
                break;
        }

        return result;
    }
}
