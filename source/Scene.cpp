#include "Scene.h"

namespace real{
    Scene::Scene(std::string_view name)
    : _name(name)
    , activeCam(nullptr)
    {}

    Result Scene::init() {
        return real::Result{"", real::Status::SUCCESS};
    }

    void Scene::update(float time) {

    }

    void Scene::resize(const glm::vec2 dimensions) {

    }
}