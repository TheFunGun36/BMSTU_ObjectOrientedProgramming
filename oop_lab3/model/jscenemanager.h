#pragma once
#include "jcomposite.h"
#include "jmanager.h"

namespace Jora {

class SceneManager : public Manager {
public:
    using SceneObjectPtr = std::weak_ptr<SceneObject>;

    void nextSceneObject(SceneObjectPtr sceneObject, const Composite& scene);
    void prevSceneObject(SceneObjectPtr sceneObject, const Composite& scene);
    void firstSceneObject(SceneObjectPtr sceneObject, const Composite& scene);
    void lastSceneObject(SceneObjectPtr sceneObject, const Composite& scene);
    void countSceneObjects(int&);
};

}