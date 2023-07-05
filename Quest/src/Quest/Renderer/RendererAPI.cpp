#include "qepch.h"
#include "Quest/Renderer/RendererAPI.h"

#include "Quest/Platform/Vulkan/VulkanRendererAPI.h"
#include "Quest/Platform/OpenGL/OpenGLRendererAPI.h"

namespace Quest
{
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OPENGL;

	Scope<RendererAPI> RendererAPI::Create()
	{
		switch (s_API)
		{
		case RendererAPI::API::NONE:		QE_CORE_ASSERT(false, "RendererAPI::NONE is not supported"); return nullptr;
		case RendererAPI::API::VULKAN:		return CreateScope<VulkanRendererAPI>();
		case RendererAPI::API::OPENGL:		return CreateScope<OpenGLRendererAPI>();
		}

		QE_CORE_ASSERT(false, "Invalid RendererAPI");
		return nullptr;
	}
}