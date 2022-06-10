#include "pch.h"
#include "jscenemanager.h"

void Jora::SceneManager::countSceneObjects(const Composite& scene, const std::weak_ptr<size_t>& result) {
    if (!result.expired())
        *result.lock() = scene.count();
}

void Jora::SceneManager::makeGroup(Composite& scene, const std::weak_ptr<ObjectId>& groupId, std::initializer_list<ObjectId> objectsId) {
    std::shared_ptr<Composite> group = std::make_shared<Composite>();
    if (!groupId.expired())
        *groupId.lock() = group->id();

    for (ObjectId id : objectsId) {
        if (scene.contains(id)) {
            group->insert(scene[id]);
            scene.remove(id);
        }
    }

    scene.insert(group);
}

void Jora::SceneManager::getLabel(const Composite& scene, const std::weak_ptr<std::string>& label, ObjectId id) {
    if (!label.expired())
        *label.lock() = scene[id]->label();
}

void Jora::SceneManager::setLabel(Composite& scene, ObjectId id, std::string&& label) {
    scene[id]->setLabel(label);
}

void Jora::SceneManager::transform(Composite& scene, std::unique_ptr<TransformAction> transformAction, ObjectId id) {
    scene[id].apply(transformAction);
}

void Jora::SceneManager::removeObject(Composite& scene, ObjectId id) {
    scene.remove(id);
}

void Jora::SceneManager::clear(Composite& scene) {
    scene.clear();
}
