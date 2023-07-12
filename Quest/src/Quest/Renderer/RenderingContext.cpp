#include "qepch.h"
#include "Quest/Renderer/RenderingContext.h"

#include "Quest/Renderer/Renderer.h"
#include "Quest/Platform/OpenGL/OpenGLContext.h"

namespace Quest
{

	Scope<RenderingContext> RenderingContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::NONE:    QE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OPENGL:	return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		QE_CORE_ASSERT(false, "Invalid RendererAPI");
		return nullptr;
	}

}