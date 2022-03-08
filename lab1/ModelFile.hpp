#pragma once
#include "Types.hpp"
#include "Exit.hpp"
#include "Model3D.hpp"

Exit fileModelLoad(Model3D *model, int &lineFailed, const Char *filename);
Exit fileModelSave(const Model3D *model, const Char *filename);
