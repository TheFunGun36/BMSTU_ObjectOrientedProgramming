#include "ExecuteCmd.hpp"
#include "Model3D.hpp"
#include "ModelFile.hpp"
#include "MemoryImpl.hpp"

static const Char *getErrorMessage(Exit exitCode) {
    const Char *msg = nullptr;

    switch (exitCode) {
        case Exit::success:
            msg = TEXT("Команда выполнена успешно");
            break;
        case Exit::fileOpenReadFail:
            msg = TEXT("Не удалось считать данные из файла");
            break;
        case Exit::modelUnininialized:
            msg = TEXT("Модель не инициализирована");
            break;
        case Exit::modelInitialized:
            msg = TEXT("Модель уже инициализирована");
            break;
        case Exit::modelScaleZero:
            msg = TEXT("Недопустимо изменение мастшаба модели с коэффициентом 0");
            break;
        case Exit::noActionToUndo:
            msg = TEXT("Нет действий для отмены");
            break;
        case Exit::inputInvalidFilename:
            msg = TEXT("Файл не найден");
            break;
        case Exit::inputCameraTooClose:
            msg = TEXT("Часть вершин распологаются за пределами камеры");
            break;
        case Exit::cmdInvalid:
            msg = TEXT("Команда не распознана");
            break;
        case Exit::noMemory:
            msg = TEXT("Недостаточно оперативной памяти");
            break;
        case Exit::nonZeroInputPtr:
            msg = TEXT("Ненулевой входной указатель");
            break;
        case Exit::sizeInvalid:
            msg = TEXT("Некорректный размер массива");
            break;
    }

    return msg;
}

Exit executeCommand(UserOutput &uOut, const UserInput &uIn, Command cmd) {
    Exit exitCode = Exit::success;
    static Model3D *model = nullptr;

    switch (cmd) {
        case Command::initialize:
            exitCode = modelInitialize(model);
            break;
        case Command::uninitialize:
            modelFree(model);
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
