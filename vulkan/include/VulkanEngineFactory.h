#pragma once
#include "RealEngine.h"
#include "VulkanScene.h"
#include "VulkanRenderer.h"
#include "VulkanWindow.h"
#include "Settings.h"

namespace vkn{

    inline real::RealEngine createEngine(std::string_view  title, glm::vec2 dim, real::Settings settings
                                         , std::unique_ptr<VulkanScene>&& scene, bool debug = false){

        auto window = std::make_unique<VulkanWindow>(title, dim, settings, debug);
        auto renderer = std::make_unique<VulkanRenderer>(debug);

        return real::RealEngine{ std::move(renderer), std::move(window), std::move(scene) };
    }

}