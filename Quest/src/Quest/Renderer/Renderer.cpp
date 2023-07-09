#include "qepch.h"
#include "Quest/Renderer/Renderer.h"

namespace Quest
{
	Scope<Renderer::SceneData> Renderer::s_SceneData = CreateScope<Renderer::SceneData>();

	void Renderer::Init()
	{
	}

	void Renderer::Shutdown()
	{
	}

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray)
	{
		shader->Bind();
		shader->SetMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);

		vertexArray->Bind();
		RenderCommand::DrawElements(vertexArray);
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{

	}
}