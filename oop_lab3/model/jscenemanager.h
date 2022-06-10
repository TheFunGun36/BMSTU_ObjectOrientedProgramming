#pragma once
#include "jcomposite.h"
#include "jmanager.h"

namespace Jora {

class SceneManager : public Manager {
public:
    using SceneObjectPtr = std::weak_ptr<SceneObject>;

    void countSceneObjects(const Composite& scene, const std::weak_ptr<size_t>& result);
    void makeGroup(Composite& scene, const std::weak_ptr<ObjectId>& groupId, std::initializer_list<ObjectId> objectsId);
    void getLabel(const Composite& scene, const std::weak_ptr<std::string>& label, ObjectId id);
    void setLabel(Composite& scene, ObjectId id, std::string&& label);
    void transform(Composite& scene, std::unique_ptr<TransformAction> transformAction, ObjectId id);
    void removeObject(Composite& scene, ObjectId id);
    void clear(Composite& scene);
};

}