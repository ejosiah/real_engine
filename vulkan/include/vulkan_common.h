#pragma once

#include "real_common.h"
#include <vulkan/vulkan.h>
#include "vk_mem_alloc.h"

namespace vkn{

    template<typename Func>
    inline Func instanceProcAddress(VkInstance instance, const std::string_view & funcName){
        return reinterpret_cast<Func>(vkGetInstanceProcAddr(instance, funcName.data()));
    }

    inline std::vector<VkLayerProperties> enumerateLayerProperties(){
        uint32_t validationLayerCount;
        vkEnumerateInstanceLayerProperties(&validationLayerCount, nullptr);

        std::vector<VkLayerProperties> layerProperties(validationLayerCount);
        vkEnumerateInstanceLayerProperties(&validationLayerCount, layerProperties.data());

        return layerProperties;
    }
}