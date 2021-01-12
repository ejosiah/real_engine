#include <algorithm>
#include "VulkanDebug.h"
#include <spdlog/spdlog.h>

namespace vkn::debug{

    inline VkDebugUtilsMessengerCreateInfoEXT  populateDebugMessengerCreateInfo(){
        VkDebugUtilsMessengerCreateInfoEXT createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        createInfo.messageSeverity =
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT    |
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT
                                 | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                                 VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        createInfo.pfnUserCallback = debugCallback;
        createInfo.pUserData = nullptr;

        return createInfo;
    }

    inline VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
            VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageType,
            const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
            void* pUserData
    ){

        if(messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT ){
            spdlog::debug(pCallbackData->pMessage);
        }
        if(messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT){
            spdlog::info(pCallbackData->pMessage);
        }
        if(messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT){
            spdlog::warn(pCallbackData->pMessage);
        }
        if(messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT){
            spdlog::error(pCallbackData->pMessage);
        }

       return VK_FALSE;
    }

    inline real::Result setupDebug(VkInstance instance, VkAllocationCallbacks* allocator){
        auto createDebugInfo = populateDebugMessengerCreateInfo();
        auto createDebugFunc = instanceProcAddress<PFN_vkCreateDebugUtilsMessengerEXT>(instance, "vkCreateDebugUtilsMessengerEXT");

        auto result = createDebugFunc(instance, &createDebugInfo, allocator, &debugMessenger);

        if(result != VK_SUCCESS){
            return { "Failed to create Debug Messenger", real::Status::FAILURE};
        }

        return {"Debug Messenger created", real::Status::SUCCESS};
    }

    inline void destroyDebug(VkInstance instance, VkAllocationCallbacks* allocator){
        auto destroyDebugFunc = instanceProcAddress<PFN_vkDestroyDebugUtilsMessengerEXT>(instance, "vkDestroyDebugUtilsMessengerEXT" );
        destroyDebugFunc(instance, debugMessenger, allocator);
    }

    inline bool checkValidationLayerSupport(){
        uint32_t validationLayerCount;
        vkEnumerateInstanceLayerProperties(&validationLayerCount, nullptr);

        std::vector<VkLayerProperties> layerProperties(validationLayerCount);
        vkEnumerateInstanceLayerProperties(&validationLayerCount, layerProperties.data());

        return std::all_of(begin(validationLayers), end(validationLayers), [&](auto& layer){
            return std::any_of(begin(layerProperties), end(layerProperties), [&layer](auto& supportedLayer){
                return strcmp(layer, supportedLayer.layerName) == 0;
            });
        });
    }
}