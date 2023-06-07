#include "qspch.h"

#include "Quasar/Core/Window.h"
#include "Quasar/Events/ApplicationEvent.h"
#include "Quasar/Events/MouseEvent.h"
#include "Quasar/Events/KeyEvent.h"


namespace Quasar
{
	// GLFW error callback for use in window creation
	static void GLFWErrorCallback(int error, const char* description)
	{
		QS_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	Window::Window(const WindowProperties& props)
	{
		Init(props);
	}

	Window::~Window()
	{
		Shutdown();
	}

	void Window::Init(const WindowProperties& props)
	{
		data.title = props.title;
		data.width = props.width;
		data.height = props.height;

		QS_CORE_INFO("Creating Window {0} ({1}, {2})", props.title, props.width, props.height);

		// Initialize GLFW
		int success = glfwInit();
		QS_CORE_ASSERT(success, "Failed to initialize GLFW :(");
		glfwSetErrorCallback(GLFWErrorCallback);

		// TODO: Setup window hints for the render api here later for debug
		m_Window = glfwCreateWindow((int)props.width, (int)props.height, data.title.c_str(), nullptr, nullptr);

		// TODO: graphics context... learn about this
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &data);
		SetVSync(true);

		// GLFW callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.width = width;
				data.height = height;

				WindowResizeEvent event(width, height);
				data.eventCallBack(event);
		});
	}

	void Window::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void Window::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void Window::SetVSync(bool enabled)
	{
		if (enabled) glfwSwapInterval(1);
		else glfwSwapInterval(0);

		m_Data.vsync = enabled;
	}
}