#pragma once
#include "Point.hpp"
#include "Exit.hpp"
#include "Model3D.hpp"

struct Action {
    enum Type {
        Move,
        Scale,
        Rotate
    };

    Type type;
    Vector3D data;
};

struct ActionList;

void actionListInitialize(ActionList *&al);
void actionListFree(ActionList *&al);
void actionListClear(ActionList *&al);

Exit actionRevert(Model3D *model, ActionList *&al);
Exit actionApply(Model3D *model, ActionList *&al, const Action &a);
