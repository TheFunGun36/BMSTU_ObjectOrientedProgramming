#include "pch.h"
#include "jcommand.h"
#include "jinitializationmanager.h"

namespace Jora {

class CAddCamera : public Command {
public:
    using Method = std::unique_ptr<Camera3D>(InitializationManager::*)();

    CAddCamera()
        : _method(&InitializationManager::createCamera3D) { 
    }

    virtual void execute(Composite& scene, Manager& manager) {
        scene.insert((dynamic_cast<InitializationManager&>(manager).*_method)());
    }

    virtual const std::type_info& neededManager() const noexcept override {
        return typeid(InitializationManager);
    }

private:
    Method _method;
};

class CAddModel : public Command {
public:
    using Method = std::unique_ptr<Model3D>(InitializationManager::*)(const std::string&);

    CAddModel(std::string&& filename)
        : _method(&InitializationManager::createModel)
        , _filename(std::move(filename)) {
    }

    virtual void execute(Composite& scene, Manager& manager) {
        scene.insert((dynamic_cast<InitializationManager&>(manager).*_method)(_filename));
    }

    virtual const std::type_info& neededManager() const noexcept override {
        return typeid(InitializationManager);
    }

private:
    Method _method;
    std::string _filename;
};

}