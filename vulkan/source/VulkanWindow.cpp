#include "VulkanWindow.h"

namespace real {

    VulkanWindow::VulkanWindow(std::string_view title, glm::vec2 dim, bool full, bool debug)
    : GlfwWindow(title, dim, full)
    , debugEnabled(debug)
    {}

    Window::WindowResult VulkanWindow::init() {
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
