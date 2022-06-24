#pragma once
#include <unordered_map>
#include <typeindex>
#include "jcomposite.h"
#include "jcommand.h"
#include "jmanager.h"

namespace Jora {

class ModelViewer {
public:
    ModelViewer();
    void execute(Command&& cmd);

    void addManager(const std::shared_ptr<Manager>& manager);
    void clear();

private:
    Composite _scene;
    std::unordered_map<std::type_index, std::shared_ptr<Manager>> _managers;
};

}
