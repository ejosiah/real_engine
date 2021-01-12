#pragma once

#include "vk_mem_alloc.h"
#include "vulkan_common.h"
#include "VulkanBuffer.h"

namespace vkn{

    struct VulkanDevice{
        VkPhysicalDevice physicalDevice;
        VkDevice  device;
        VkPhysicalDeviceProperties properties;
        VkPhysicalDeviceFeatures features;
        VkPhysicalDeviceFeatures enabledFeatures;
        std::vector<VkQueueFamilyProperties> queueFamilyProperties;
        std::vector<VkExtensionProperties> supportedExtensions;
        VmaAllocator  memoryAllocator;

        explicit VulkanDevice(VkPhysicalDevice pDevice);

        ~VulkanDevice();

        inline operator VkDevice() const {
            return device;
        }

        bool checkDeviceExtensionSupport(std::vector<VkExtensionProperties> requiredExtensions);

        std::vector<VkExtensionProperties> extensions();

        uint32_t        getMemoryType(uint32_t typeBits, VkMemoryPropertyFlags properties, VkBool32 *memTypeFound = nullptr) const;
        uint32_t        getQueueFamilyIndex(VkQueueFlagBits queueFlags) const;
        VkResult        createLogicalDevice(VkPhysicalDeviceFeatures enabledFeatures, std::vector<const char *> enabledExtensions, void *pNextChain, bool useSwapChain = true, VkQueueFlags requestedQueueTypes = VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_COMPUTE_BIT);
        VkResult        createBuffer(VkBufferUsageFlags usageFlags, VkMemoryPropertyFlags memoryPropertyFlags, VkDeviceSize size, VkBuffer *buffer, VkDeviceMemory *memory, void *data = nullptr);
        VkResult        createBuffer(VkBufferUsageFlags usageFlags, VkMemoryPropertyFlags memoryPropertyFlags, Buffer *buffer, VkDeviceSize size, void *data = nullptr);
     //   void            copyBuffer(vks::Buffer *src, vks::Buffer *dst, VkQueue queue, VkBufferCopy *copyRegion = nullptr);
        VkCommandPool   createCommandPool(uint32_t queueFamilyIndex, VkCommandPoolCreateFlags createFlags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT);
        VkCommandBuffer createCommandBuffer(VkCommandBufferLevel level, VkCommandPool pool, bool begin = false);
        VkCommandBuffer createCommandBuffer(VkCommandBufferLevel level, bool begin = false);
        void            flushCommandBuffer(VkCommandBuffer commandBuffer, VkQueue queue, VkCommandPool pool, bool free = true);
        void            flushCommandBuffer(VkCommandBuffer commandBuffer, VkQueue queue, bool free = true);
        bool            extensionSupported(std::string extension);
        VkFormat        getSupportedDepthFormat(bool checkSamplingSupport);
    };
}