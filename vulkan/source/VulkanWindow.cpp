#include "VulkanWindow.h"

namespace vkn {

    real::Either_t<VkSurfaceKHR> VulkanGraphicsContext::getSurface(VkInstance instance) {
        if(surface != VK_NULL_HANDLE){
            return std::make_tuple(real::Result{"Surface created", real::Status::SUCCESS}, surface);
        }
        auto result = glfwCreateWindowSurface(instance, window, nullptr, &surface);
        if(result != VK_SUCCESS) {
            return std::make_tuple(
                    real::Result{"Unable to create Surface", real::Status::FAILURE}
                    , surface);
        }

        return std::make_tuple(real::Result{"Surface created", real::Status::SUCCESS}, surface);
    }

    VulkanWindow::VulkanWindow(std::string_view title, glm::vec2 dim, real::Settings settings, bool debug)
    : GlfwWindow(title, dim, settings)
    , debugEnabled(debug)
    {}

    real::Result VulkanWindow::init() {
        auto result = GlfwWindow::init();
        uint32_t count;
        auto glfwExtensions = glfwGetRequiredInstanceExtensions(&count);
        std::vector<const char*> extensions{glfwExtensions, glfwExtensions + count};

        if(debugEnabled){
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }
        graphicsContext.instanceExtensions = std::move(extensions);
        return result;
    }

    void VulkanWindow::setWindowHints() {
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    }
}
