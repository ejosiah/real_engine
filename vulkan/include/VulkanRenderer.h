#pragma once

#include <vector>
#include <vulkan/vulkan.h>
#include "Renderer.h"

namespace vkn{
    class VulkanRenderer : public real::Renderer{
    public:
        VulkanRenderer(bool debug = false);

        ~VulkanRenderer();

        real::Result init(const real::GraphicsContext& gContext, const real::Scene& scene) override;

        void render(const real::Scene& scene) override;

        void resize(const glm::vec2& dimensions) override;

    private:
        VkResult createInstance(const std::vector<const char*>& extensions, const char* appName);

    private:
        VkInstance instance;
        VkAllocationCallbacks* allocator = nullptr;
        std::vector<const char*> validationLayers;
        bool debugEnabled = false;
    };

}