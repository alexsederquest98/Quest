#include "qepch.h"
#define VMA_IMPLEMENTATION

#include "Quest/Platform/Vulkan/VulkanDevice.h"
#include "Quest/Platform/Vulkan/VulkanContext.h"

namespace Quest
{
	static bool CheckDeviceExtensionSupport(VkPhysicalDevice device, std::vector<const char*> extensions)
    {
        uint32_t extensionCount;
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> availableExtensions(extensionCount);
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

        std::set<std::string> requiredExtensions(extensions.begin(), extensions.end());

        for (const auto& extension : availableExtensions)
        {
            requiredExtensions.erase(extension.extensionName);
        }

        return requiredExtensions.empty();
    }

    static QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface)
    {
        QueueFamilyIndices indices;

        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

        int i = 0;
        for (const auto& queueFamily : queueFamilies)
        {
            if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
            {
                indices.Graphics = i;
            }

            VkBool32 presentSupport = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);

            if (presentSupport)
            {
                indices.Present = i;
            }

            if (indices.isComplete())
            {
                break;
            }

            i++;
        }

        return indices;
    }

    VulkanPhysicalDevice::VulkanPhysicalDevice(const std::vector<const char*>& requiredExtensions)
    {

    }

    VulkanDevice::VulkanDevice(Ref<VulkanPhysicalDevice> device, VkSurfaceKHR* surface, const std::vector<const char*>& requiredExtensions, const std::vector<const char*>& requiredLayers)
    {
        QueueFamilyIndices indices = findQueueFamilies(device.get()->Get(), *surface);

        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
        std::set<uint32_t> uniqueQueueFamilies = { indices.Graphics.value(), indices.Present.value() };

        float queuePriority = 1.0f;
        for (uint32_t queueFamily : uniqueQueueFamilies)
        {
            VkDeviceQueueCreateInfo queueCreateInfo{};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo.queueFamilyIndex = queueFamily;
            queueCreateInfo.queueCount = 1;
            queueCreateInfo.pQueuePriorities = &queuePriority;
            queueCreateInfos.push_back(queueCreateInfo);
        }

        VkPhysicalDeviceFeatures deviceFeatures{};

        VkDeviceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

        createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
        createInfo.pQueueCreateInfos = queueCreateInfos.data();

        createInfo.pEnabledFeatures = &deviceFeatures;

        createInfo.enabledExtensionCount = static_cast<uint32_t>(requiredExtensions.size());
        createInfo.ppEnabledExtensionNames = requiredExtensions.data();

        if (enableValidationLayers)
        {
            createInfo.enabledLayerCount = static_cast<uint32_t>(requiredLayers.size());
            createInfo.ppEnabledLayerNames = requiredLayers.data();
        }
        else
        {
            createInfo.enabledLayerCount = 0;
        }

        if (vkCreateDevice(device.get()->Get(), &createInfo, nullptr, &m_LogicalDevice) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create logical device :(");
        }

        vkGetDeviceQueue(m_LogicalDevice, indices.Graphics.value(), 0, &m_GraphicsQueue);
        vkGetDeviceQueue(m_LogicalDevice, indices.Present.value(), 0, &m_PresentQueue);
    }

    VulkanDevice::~VulkanDevice()
    {
        vmaDestroyAllocator(m_Allocator);
        vkDestroyDevice(m_LogicalDevice, nullptr);

        QE_INFO("Vulkan Device destroyed");
    }
}