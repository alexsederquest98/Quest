#pragma once

#include "Quasar/Core/Base.h"
#include "Quasar/Events/Event.h"
#include "Quasar/Events/ApplicationEvent.h"
#include "Quasar/Core/Window.h"
#include <functional>

namespace Quasar
{

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);
		void Close();
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		Window* m_Window;
		bool m_Running = true;
	};

	// Define in client
	Application* CreateApplication();
}