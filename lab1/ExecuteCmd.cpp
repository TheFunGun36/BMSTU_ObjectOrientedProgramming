#include "ExecuteCmd.hpp"
#include "Model3D.hpp"
#include "ModelFile.hpp"

static const char *getErrorMessage(Exit exitCode) {
    const char *msg = nullptr;

    switch (exitCode) {
        case Exit::success:
            msg = "Команда выполнена успешно";
            break;
        case Exit::fileOpenReadFail:
            msg = "Не удалось считать данные из файла";
            break;
        case Exit::modelUnininialized:
            msg = "Модель не инициализирована";
            break;
        case Exit::modelInitialized:
            msg = "Модель уже инициализирована";
            break;
        case Exit::modelScaleZero:
            msg = "Недопустимо изменение мастшаба модели с коэффициентом 0";
            break;
        case Exit::noActionToUndo:
            msg = "Нет действий для отмены";
            break;
        case Exit::inputInvalidFilename:
            msg = "Файл не найден";
            break;
        case Exit::inputCameraTooClose:
            msg = "Часть вершин распологаются за пределами камеры";
            break;
        case Exit::cmdInvalid:
            msg = "Команда не распознана";
            break;
        case Exit::noMemory:
            msg = "Недостаточно оперативной памяти";
            break;
        case Exit::nonZeroInputPtr:
            msg = "Ненулевой входной указатель";
            break;
        case Exit::sizeInvalid:
            msg = "Некорректный размер массива";
            break;
        case Exit::modelInvalidVertexId:
            msg = "В исходном файле задан некорректный индекс вершины";
            break;
        default:
            msg = "Неизвестная ошибка";
    }

    return msg;
}

Exit executeCommand(UserOutput &uOut, const UserInput &uIn, Command cmd) {
    Exit exitCode = Exit::success;
    static Model3D model = modelEmpty();

    switch (cmd) {
        case Command::uninitialize:
            modelClear(model);
            break;
        case Command::modelLoad:
            exitCode = fileModelLoad(model, uIn.filename);
            break;
        case Command::modelProjectPerspective:
            exitCode = modelProjectPerspective(uOut.projection, model, uIn.cameraDistance);
            break;
        case Command::modelProjectOrhogonal:
            exitCode = modelProjectOrthogonal(uOut.projection, model);
            break;
        case Command::modelMove:
            exitCode = modelMove(model, uIn.actionVector);
            break;
        case Command::modelScale:
            exitCode = modelScale(model, uIn.actionVector);
            break;
        case Command::modelRotate: 
            exitCode = modelRotate(model, uIn.actionVector);
            break;
        case Command::getErrorMessage:
            uOut.errorMessage = getErrorMessage(uIn.exitCode);
            break;
        default:
            exitCode = Exit::cmdInvalid;
    }

    return exitCode;
}
