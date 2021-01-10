#pragma once

#include <vector>
#include "glfw_window.h"
#include <vulkan/vulkan.h>

namespace real {

    struct VulkanGraphicsContext : public GraphicsContext{
        std::vector<const char*> instanceExtensions;
    };

    class VulkanWindow : public GlfwWindow{
    public:
        VulkanWindow(std::string_view title, glm::vec2 dim, bool full = false, bool debug = false);

        WindowResult init() override;

        [[nodiscard]] virtual const  VulkanGraphicsContext& getContext()  const override{
            return graphicsContext;
        }

        virtual void setWindowHints() override;

    private:
        VulkanGraphicsContext graphicsContext;
        bool debugEnabled;
    };
}