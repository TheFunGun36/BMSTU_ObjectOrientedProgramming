#pragma once
#include "Exit.hpp"
#include "Model3D.hpp"

Exit fileModelLoad(Model3D *model, int &lineFailed, const char *filename);
Exit fileModelSave(const Model3D *model, const char *filename);
