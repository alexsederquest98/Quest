#pragma once

#include "Quest/Core/Base.h"

namespace Quest
{
	class RenderingContext
	{
	public:
		virtual ~RenderingContext() = default;

		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;

		static Scope<RenderingContext> Create(void* window);
	};
}