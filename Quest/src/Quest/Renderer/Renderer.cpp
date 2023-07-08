#include "qepch.h"
#include "Quest/Renderer/Renderer.h"

namespace Quest
{
	void Renderer::Init()
	{
	}

	void Renderer::Shutdown()
	{
	}

	void Renderer::BeginScene()
	{
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray)
	{
		shader->Bind();

		vertexArray->Bind();
		RenderCommand::DrawElements(vertexArray);
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{

	}
}