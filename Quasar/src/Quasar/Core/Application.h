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
	private:
		Window* m_Window;
		bool m_Running = true;
	};

	// Define in client
	Application* CreateApplication();
}