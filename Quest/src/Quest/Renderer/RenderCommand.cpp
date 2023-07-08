#include "qepch.h"
#include "Quest/Renderer/RenderCommand.h"

#include "Quest/Platform/OpenGL/OpenGLRendererAPI.h"

namespace Quest
{
	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();

	void RenderCommand::Init()
	{
		s_RendererAPI->Init();
	}

	void RenderCommand::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		s_RendererAPI->SetViewport(x, y, width, height);
	}

	void RenderCommand::SetClearColor(const glm::vec4& color)
	{
		s_RendererAPI->SetClearColor(color);
	}

	void RenderCommand::Clear()
	{
		s_RendererAPI->Clear();
	}

	void RenderCommand::DrawElements(const Ref<VertexArray>& vertexArray)
	{
		s_RendererAPI->DrawElements(vertexArray);
	}
}