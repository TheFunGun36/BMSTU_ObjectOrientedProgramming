#include "Action.hpp"
#include "MemoryImpl.hpp"
#include "Point.hpp"

typedef ActionList Node;
struct ActionList {
    Action action;
    Node *prevAction;
};

static Exit invertAction(Action &a) {
    Exit ec = Exit::success;

    if (a.type == Action::Scale) {
        if (isZero(a.data.x) || isZero(a.data.y) || isZero(a.data.z)) {
            ec = Exit::modelScaleZero;
        }
        else {
            a.data.x = 1 / a.data.x;
            a.data.y = 1 / a.data.y;
            a.data.z = 1 / a.data.z;
        }
    }
    else {
        a.data.x = -a.data.x;
        a.data.y = -a.data.y;
        a.data.z = -a.data.z;
    }

    return ec;
}

static Exit modelApplyAction(Model3D *model, const Action &a) {
    Exit ec = model ? Exit::success : Exit::modelUnininialized;

    if (isOk(ec)) {
        switch (a.type) {
            case Action::Move:   ec = modelMove(model, a.data);   break;
            case Action::Rotate: ec = modelRotate(model, a.data); break;
            case Action::Scale:  ec = modelScale(model, a.data);  break;
            default:             ec = Exit::actionUnknown;
        }
    }

    return ec;
}

static void actionPop(Node *&head) {
    if (head) {
        Node *toDelete = head;
        head = head->prevAction;
        free(toDelete);
    }
}

void actionListInitialize(ActionList *&head) {
}

void actionListFree(ActionList *&head) {
    actionListClear(head);
}

void actionListClear(ActionList *&head) {
    while (head)
        actionPop(head);
}

Exit actionRevert(Model3D *model, ActionList *&head) {
    Exit ec = head ? Exit::success : Exit::noActionToUndo;

    Action a;
    if (isOk(ec)) {
        a = head->action;
        ec = invertAction(a);
    }

    if (isOk(ec))
        ec = modelApplyAction(model, a);

    if (isOk(ec))
        actionPop(head);

    return ec;
}

Exit actionApply(Model3D *model, ActionList *&head, const Action &a) {
    Exit ec = head ? Exit::success : Exit::noActionToUndo;

    if (isOk(ec))
        ec = modelApplyAction(model, head->action);

    if (isOk(ec))
        actionPop(head);

    return ec;
}
