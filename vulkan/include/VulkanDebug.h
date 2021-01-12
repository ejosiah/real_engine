#pragma once

#include <vector>
#include "real_common.h"
#include "vulkan_common.h"

namespace vkn::debug{

    static VkDebugUtilsMessengerEXT debugMessenger;

    const std::vector<const char*> validationLayers = {
            "VK_LAYER_KHRONOS_validation"
    };

    extern VkDebugUtilsMessengerCreateInfoEXT  populateDebugMessengerCreateInfo();


    VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
            VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageType,
            const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
            void* pUserData
    );

    real::Result setupDebug(VkInstance instance, VkAllocationCallbacks* allocator = nullptr);

    void destroyDebug(VkInstance instance, VkAllocationCallbacks* allocator = nullptr);

    extern bool checkValidationLayerSupport();
}