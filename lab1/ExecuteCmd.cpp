#include "ExecuteCmd.hpp"
#include "Model3D.hpp"
#include "ModelFile.hpp"
#include "Action.hpp"
#include "MemoryImpl.hpp"

static const Char *getErrorMessage(Exit exitCode) {
    const Char *msg = nullptr;

    switch (exitCode) {
        case Exit::success:
            msg = "Команда выполнена успешно";
            break;
        case Exit::fileOpenReadFail:
            msg = "Не удалось считать данные из файла";
            break;
        case Exit::fileOpenWriteFail:
            msg = "Не удалось записать данные в файл";
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
    }

    return msg;
}

static inline Action::Type actionTypeByCommand(Command cmd) {
    return (Action::Type)((int)cmd - (int)Command::modelMove);
}

Exit executeCommand(UserOutput &uOut, const UserInput &uIn, Command cmd) {
    Exit exitCode = Exit::success;
    static Model3D *model = nullptr;
    static ActionList *actionList = nullptr;

    switch (cmd) {
        case Command::initialize:
            exitCode = modelInitialize(model);
            if (exitCode == Exit::success)
                actionListInitialize(actionList);
            else
                modelFree(model);
            break;
        case Command::uninitialize:
            modelFree(model);
            actionListFree(actionList);
            break;
        case Command::modelLoad:
            exitCode = fileModelLoad(model, uOut.lineFailed, uIn.filename);
            if (exitCode == Exit::success)
                actionListClear(actionList);
            break;
        case Command::modelSave:
            exitCode = fileModelSave(model, uIn.filename);
            break;
        case Command::modelProjectPerspective:
            exitCode = modelProjectPerspective(uOut.projection, model, uIn.cameraDistance);
            break;
        case Command::modelProjectOrhogonal:
            exitCode = modelProjectOrthogonal(uOut.projection, model);
            break;
        case Command::modelMove: [[fallthrough]];
        case Command::modelScale: [[fallthrough]];
        case Command::modelRotate: {
            Action action;
            action.type = actionTypeByCommand(cmd);
            action.data = uIn.actionVector;
            exitCode = actionApply(model, actionList, action);
            break;
        }
        case Command::modelUndoAction:
            exitCode = actionRevert(model, actionList);
            break;
        case Command::getErrorMessage:
            uOut.errorMessage = getErrorMessage(uIn.exitCode);
            break;
        default:
            exitCode = Exit::cmdInvalid;
    }

    return exitCode;
}
