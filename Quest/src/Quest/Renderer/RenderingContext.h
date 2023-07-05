#pragma once

#include "Quest/Core/Base.h"
#include <GLFW/glfw3.h>

namespace Quest
{
	class RenderingContext
	{
	public:
		virtual ~RenderingContext() = default;

		virtual void Init() = 0;
		virtual void Shutdown() = 0;
		virtual void WaitForDevice() = 0;
		virtual void SwapBuffers() = 0;

		static Scope<RenderingContext> Create(GLFWwindow* window);
	};
}