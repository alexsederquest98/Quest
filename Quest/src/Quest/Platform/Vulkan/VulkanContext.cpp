#include "qepch.h"
#include "Quest/Platform/Vulkan/VulkanContext.h"

namespace Quest
{
	VulkanContext::VulkanContext(GLFWwindow* window)
		: m_Window(window)
	{

	}

	void VulkanContext::Init()
	{
		glfwMakeContextCurrent(m_Window);
	}

	void VulkanContext::Shutdown()
	{

	}

	void VulkanContext::WaitForDevice()
	{

	}

	void VulkanContext::SwapBuffers()
	{

	}
}