#pragma once

#include "Quest/Core/Base.h"
#include "Quest/Renderer/RendererAPI.h"
#include "Quest/Renderer/RenderCommand.h"
#include "Quest/Renderer/Shader.h"
#include "Quest/Renderer/OrthographicCamera.h"

namespace Quest
{
	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(OrthographicCamera& camera); // update with params
		static void EndScene();

		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

		static void OnWindowResize(uint32_t width, uint32_t height);

		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static Scope<SceneData> s_SceneData;
	};
}