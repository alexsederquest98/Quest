#include "qspch.h"

#include "Quasar/Core/Application.h"
//#include "Quasar/Events/ApplicationEvent.h"
#include "Quasar/Core/Logger.h"

namespace Quasar
{
	#define BIND_EVENT_CALLBACK(x) std::bind(&Application::x, this, std::placeholders::_1)
	Application::Application()
	{
		m_Window = new Window(WindowProperties());
		m_Window->SetEventCallback(BIND_EVENT_CALLBACK(OnEvent));
	}

	Application::~Application()
	{
		delete m_Window;
	}

	void Application::Run()
	{
		while (m_Running)
		{
			m_Window->OnUpdate();
		}
	}

	void Application::Close()
	{
		m_Running = false;
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_CALLBACK(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_CALLBACK(Application::OnWindowResize));
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		return false;
	}
}