#pragma once
#include "Quest/Renderer/RendererAPI.h"

namespace Quest
{
	class VulkanRendererAPI : public RendererAPI
	{
	public:
		virtual void Init() override;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
	};
}