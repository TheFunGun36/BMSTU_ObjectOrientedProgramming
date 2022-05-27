#pragma once
#include "jcomposite.h"
#include "jcommand.h"
#include "jmanager.h"
#include <unordered_map>

namespace Jora {

class ModelViewer {
public:
    void execute(Command&& cmd);

    void addManager(const std::shared_ptr<Manager>& manager);
    void clear();

private:
    Composite _scene;
    Composite _selection;
    std::unordered_map<const std::type_info&, std::shared_ptr<Manager>> _managers;
};

}
