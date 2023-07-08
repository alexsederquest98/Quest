#pragma once
#include "Quest/Renderer/RendererAPI.h"

namespace Quest
{
	class RenderCommand
	{
	public:
		static void Init();
		static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
		static void SetClearColor(const glm::vec4& color);
		static void Clear();
		static void DrawElements(const Ref<VertexArray>& vertexArray);
	private:
		static Scope<RendererAPI> s_RendererAPI;
	};
}