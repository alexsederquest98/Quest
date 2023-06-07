#include "qspch.h"

#include "Quasar/Core/Application.h"
//#include "Quasar/Events/ApplicationEvent.h"
#include "Quasar/Core/Logger.h"

namespace Quasar
{
#define BIND_TEST(x) std::bind(&Application::x, this, std::placeholders::_1)
	Application::Application()
	{
		m_Window = new Window(WindowProperties());
		m_Window->SetEventCallback(BIND_TEST(OnEvent));
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

	void Application::OnEvent(Event& e)
	{

	}
}