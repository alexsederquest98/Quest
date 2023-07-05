#pragma once

#include "Quest/Renderer/RenderingContext.h"

#include "Quest/Platform/OpenGL/OpenGLBase.h"

namespace Quest
{
	class OpenGLContext : public RenderingContext
	{
	public:
		OpenGLContext(GLFWwindow* window);

		virtual void Init() override;
		virtual void Shutdown() override;
		virtual void SwapBuffers() override;
		virtual void WaitForDevice() override;
	private:
		GLFWwindow* m_WindowHandle;
	};
}