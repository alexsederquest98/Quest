#pragma once

#include "Quest/Platform/Vulkan/VulkanBase.h"

namespace Quest
{
	struct QueueFamilyIndices
	{
		std::optional<uint32_t> Graphics;
		std::optional<uint32_t> Present;

		bool isComplete()
		{
			return Graphics.has_value() && Present.has_value();
		}
	};

	class VulkanPhysicalDevice
	{
	public:
		VulkanPhysicalDevice(const std::vector<const char*>& requiredExtensions);

		VkPhysicalDevice Get() { return m_PhysicalDevice; }
		VkPhysicalDeviceProperties GetProperties() { return m_Properties; }

	private:
		VkPhysicalDevice m_PhysicalDevice;
		VkPhysicalDeviceProperties m_Properties;

		VkFormat m_DepthFormat;
	};

	class VulkanDevice
	{
	public:
		VulkanDevice(Ref<VulkanPhysicalDevice> device, VkSurfaceKHR* surface, const std::vector<const char*>& requiredExtensions, const std::vector<const char*>& requiredLayers);
		~VulkanDevice();

		VkDevice Get() { return m_LogicalDevice; }
		VkQueue GetGraphicsQueue() { return m_GraphicsQueue; }
		VkQueue GetPresentQueue() { return m_PresentQueue; }

		VmaAllocator GetAllocator() { return m_Allocator; }
		const QueueFamilyIndices& GetQueueFamilyIndices() const { return m_QueueFamilyIndices; }
	private:
		VkDevice m_LogicalDevice;
		VkQueue m_GraphicsQueue;
		VkQueue m_PresentQueue;
		VmaAllocator m_Allocator;

		#ifdef QE_DEBUG
		const bool enableValidationLayers = true;
		#else
		const bool enableValidationLayers = false;
		#endif

		QueueFamilyIndices m_QueueFamilyIndices;
	};
}