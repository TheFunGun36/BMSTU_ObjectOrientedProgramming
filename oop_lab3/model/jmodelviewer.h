#pragma once
#include "jcomposite.h"
#include "jcommand.h"
#include "jmanager.h"
#include <map>

namespace Jora {

class ModelViewer {
public:
    void execute(Command&& cmd);

    void addManager(Manager&& manager);
    Manager& manager(const std::type_info& managerType);
    void clear();
private:
    Composite _scene;
    std::map<const std::type_info&, Manager> _managers;
};

}
