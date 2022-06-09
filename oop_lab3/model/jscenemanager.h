#pragma once
#include "jcomposite.h"
#include "jmanager.h"

namespace Jora {

class SceneManager : public Manager {
public:
    using SceneObjectPtr = std::weak_ptr<SceneObject>;

    void countSceneObjects(const std::weak_ptr<size_t>& result);
    void makeGroup(const std::weak_ptr<size_t>& groupId, std::initializer_list<size_t> objectsId);
    void getLabel(const std::weak_ptr<std::string>& label, ObjectId id);
    void setLabel(ObjectId id, std::string&& label);
    void removeObject(Composite& scene, ObjectId id);
    void clear(Composite& scene);
};

}