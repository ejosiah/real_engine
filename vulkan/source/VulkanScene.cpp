#include "VulkanScene.h"

namespace vkn {

    VulkanScene::VulkanScene(std::string_view name) : real::Scene(name) {}

    real::Result VulkanScene::init() {
        return real::Scene::init();
    }
}