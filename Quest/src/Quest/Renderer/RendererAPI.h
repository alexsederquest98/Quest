#pragma once

#include "Quest/Core/Base.h"
#include "Quest/Math/Math.h"

namespace Quest
{
	class RendererAPI
	{
	public:
		enum class API
		{
			NONE = 0, VULKAN = 1, OPENGL = 2
		};
	public:
		virtual ~RendererAPI() = default;

		virtual void Init() = 0;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		static API GetAPI() { return s_API; }
		static Scope<RendererAPI> Create();
	private:
		static API s_API;
	};
}