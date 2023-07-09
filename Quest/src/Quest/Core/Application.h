#pragma once

#include "Quest/Core/Base.h"
#include "Quest/Events/Event.h"
#include "Quest/Events/ApplicationEvent.h"
#include "Quest/Core/Window.h"
#include "Quest/ImGui/ImGuiLayer.h"
#include "Quest/Core/LayerStack.h"
#include "Quest/Core/Timestep.h"
#include <functional>

#include "Quest/Renderer/Shader.h"
#include "Quest/Renderer/Buffer.h"
#include "Quest/Renderer/VertexArray.h"
#include "Quest/Renderer/OrthographicCamera.h"

int main(int argc, char** argv);

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

		static Application& Get() { return *s_Instance; }
		Window& GetWindow() { return *m_Window; }

		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

		void Close();
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		Scope<Window> m_Window;
		bool m_Running = true;
		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;
		friend int ::main(int argc, char** argv);
	};

	// Define in client
	Application* CreateApplication();
}