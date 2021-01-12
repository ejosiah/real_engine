#pragma once


#include <vector>
#include "vulkan_common.h"
#include "glfw_window.h"
#include <vulkan/vulkan.h>

namespace vkn {



    struct VulkanGraphicsContext : public real::GraphicsContext{
        GLFWwindow * window = nullptr;
        std::vector<const char*> instanceExtensions;

        real::Either_t<VkSurfaceKHR> getSurface(VkInstance instance);

    private:
        VkSurfaceKHR  surface = VK_NULL_HANDLE;
    };

    class VulkanWindow : public real::GlfwWindow{
    public:
        VulkanWindow(std::string_view title, glm::vec2 dim, real::Settings settings, bool debug = false);

        real::Result init() override;

        [[nodiscard]] const  VulkanGraphicsContext& getContext()  const override{
            return graphicsContext;
        }

        void setWindowHints() override;

    private:
        VulkanGraphicsContext graphicsContext;
        bool debugEnabled;
    };
}