#include "VulkanRenderer.h"
#include "VulkanWindow.h"
#include "VulkanDebug.h"

namespace vkn{

    VulkanRenderer::VulkanRenderer(bool debug)
    : debugEnabled(debug)
    {
    }

    VulkanRenderer::~VulkanRenderer(){
        vkDestroyInstance(instance, nullptr);
    }

    real::Result VulkanRenderer::init(const real::GraphicsContext &gContext, const real::Scene &scene) {
        if(debugEnabled && !vkn::debug::checkValidationLayerSupport()){
            return {"validation layers requested but not available"};
        }

        auto& extensions = dynamic_cast<const VulkanGraphicsContext&>(gContext).instanceExtensions;
        auto vkRes = createInstance(extensions, scene.name().data());
        if(vkRes != VK_SUCCESS){
            return {"Failed to initialize Vulkan Renderer", real::Status::FAILURE};
        }
        return {"Vulkan Renderer Instance initialized"};
    }

    VkResult VulkanRenderer::createInstance(const std::vector<const char *>& extensions, const char* appName) {
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Real Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(0, 0, 0);
        appInfo.pApplicationName = appName;
        appInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 0);
        appInfo.apiVersion = VK_VERSION_1_2;

        VkDebugUtilsMessengerCreateInfoEXT debugInfo = vkn::debug::populateDebugMessengerCreateInfo();

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pNext = &debugInfo;
        createInfo.pApplicationInfo = &appInfo;
        createInfo.enabledExtensionCount = extensions.size();
        createInfo.ppEnabledExtensionNames = extensions.data();

        if(debugEnabled){
            createInfo.enabledLayerCount = validationLayers.size();
            createInfo.ppEnabledLayerNames = validationLayers.data();
        }

        return vkCreateInstance(&createInfo, allocator, &instance);
    }

    void VulkanRenderer::render(const real::Scene &scene) {

    }

    void VulkanRenderer::resize(const glm::vec2 &dimensions) {

    }

}