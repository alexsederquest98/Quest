#include "qepch.h"
#include "Quest/Renderer/RenderingContext.h"

#include "Quest/Renderer/Renderer.h"
#include "Quest/Platform/Vulkan/VulkanContext.h"

namespace Quest
{

	Scope<RenderingContext> RenderingContext::Create(GLFWwindow* window)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::NONE:    QE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::VULKAN:  return CreateScope<VulkanContext>(window);
		}

		QE_CORE_ASSERT(false, "Invalid RendererAPI");
		return nullptr;
	}

}