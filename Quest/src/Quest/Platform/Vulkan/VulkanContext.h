#pragma once

#include "Quest/Renderer/RenderingContext.h"
#include "Quest/Renderer/Renderer.h"

#include "Quest/Platform/Vulkan/VulkanBase.h"
#include "Quest/Platform/Vulkan/VulkanDevice.h"

namespace Quest
{
	class VulkanContext : public RenderingContext
	{
	public:
		VulkanContext(GLFWwindow* window);
		void Init() override;
		void Shutdown() override;
		void WaitForDevice() override;

		//static Ref<VulkanContext> Get() { return DynamicPointerCast<VulkanContext>(Renderer::GetContext()); }

		VkInstance GetInstance() { return m_Instance; }
		VkSurfaceKHR GetSurface() { return m_Surface; }

		Ref<VulkanPhysicalDevice> GetPhysicalDevice() { return m_PhysicalDevice; }
		Ref<VulkanDevice> GetDevice() { return m_LogicalDevice; }
	private:
		GLFWwindow* m_Window;

		VkInstance m_Instance;
		VkSurfaceKHR m_Surface;

		Ref<VulkanPhysicalDevice> m_PhysicalDevice;
		Ref<VulkanDevice> m_LogicalDevice;
	};
}