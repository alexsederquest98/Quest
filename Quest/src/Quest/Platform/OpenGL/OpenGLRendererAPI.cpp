#include "qepch.h"

#include "Quest/Platform/OpenGL/OpenGLRendererAPI.h"

namespace Quest
{
	void OpenGLMessageCallback(unsigned source, unsigned type, unsigned id, unsigned severity,
							   int length, const char* message, const void* userParameter)
	{
		switch (severity)
		{
		case GL_DEBUG_SEVERITY_NOTIFICATION:	QE_CORE_TRACE(message); return;
		case GL_DEBUG_SEVERITY_LOW:				QE_CORE_WARN(message); return;
		case GL_DEBUG_SEVERITY_MEDIUM:			QE_CORE_ERROR(message); return;
		case GL_DEBUG_SEVERITY_HIGH:			QE_CORE_CRITICAL(message); return;
		}

		QE_CORE_ASSERT(false, "Invalid severity level");
	}

	void OpenGLRendererAPI::Init()
	{
	#ifdef QE_DEBUG
		glEnable(GLAD_GL_KHR_debug);
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(OpenGLMessageCallback, nullptr);
		// GL_DEBUG_SEVERITY_NOTIFICATION
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
	#endif

		// Enable global state features of OpenGL
		//glEnable(GL_BLEND);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//glEnable(GL_DEPTH_TEST);
		//glEnable(GL_LINE_SMOOTH);
	}

	void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}