#pragma once

#include "Quest/Core/Base.h"
#include "Quest/Events/Event.h"
#include "Quest/Events/ApplicationEvent.h"
#include "Quest/Core/Window.h"
#include "Quest/Core/LayerStack.h"
#include <functional>

namespace Quest
{

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);
		
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		void Close();
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		Window* m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	// Define in client
	Application* CreateApplication();
}