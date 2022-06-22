#pragma once
#include "pch.h"
#include "jcommand.h"
#include "jinitializationmanager.h"

namespace Jora {

class CAddCamera : public Command {
public:
    using Method = std::unique_ptr<Camera3D>(InitializationManager::*)();

    CAddCamera(const std::shared_ptr<ObjectId>& resultId)
        : _method(&InitializationManager::createCamera3D)
        , _resultId(resultId) {
    }

    virtual void execute(Composite& scene, Manager& manager) {
        auto result = (dynamic_cast<InitializationManager&>(manager).*_method)();
        if (result) {
            *_resultId = result->id();
            scene.insert(std::move(result));
        }
    }

    virtual const std::type_info& neededManager() const noexcept override {
        return typeid(InitializationManager);
    }

private:
    Method _method;
    std::shared_ptr<ObjectId> _resultId;
};

class CAddModel : public Command {
public:
    using Method = std::unique_ptr<Model3D>(InitializationManager::*)(const std::string&);

    CAddModel(std::string&& filename, const std::shared_ptr<ObjectId>& resultId)
        : _method(&InitializationManager::createModel)
        , _filename(std::move(filename))
        , _resultId(resultId) {
    }

    virtual void execute(Composite& scene, Manager& manager) {
        auto result = (dynamic_cast<InitializationManager&>(manager).*_method)(_filename);
        if (result) {
            *_resultId = result->id();
            scene.insert(std::move(result));
        }
    }

    virtual const std::type_info& neededManager() const noexcept override {
        return typeid(InitializationManager);
    }

private:
    Method _method;
    std::string _filename;
    std::shared_ptr<ObjectId> _resultId;
};

}