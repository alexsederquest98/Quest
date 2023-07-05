#include "qepch.h"

#include "OpenGLContext.h"

namespace Quest
{
	OpenGLContext::OpenGLContext(GLFWwindow* window)
		: m_WindowHandle(window)
	{
		QE_CORE_ASSERT(window, "Window is NULL");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		QE_CORE_ASSERT(status, "Failed to initialize Glad");

		// Check to make sure the version of OpenGL is 4.6 capable
		//QE_CORE_INFO("OpenGL Version Information:");
		//QE_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		//QE_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		//QE_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::Shutdown()
	{

	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

	void OpenGLContext::WaitForDevice()
	{

	}
}