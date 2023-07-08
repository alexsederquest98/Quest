#pragma once

#include "Quest/Core/Base.h"
#include "Quest/Events/Event.h"
#include "Quest/Events/ApplicationEvent.h"
#include "Quest/Core/Window.h"
#include "Quest/Core/LayerStack.h"
#include <functional>

#include "Quest/Renderer/Shader.h"
#include "Quest/Renderer/Buffer.h"
#include "Quest/Renderer/VertexArray.h"

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

		void Close();
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		Window* m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;

		// Testing
		Ref<Shader> m_Shader;
		unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;
		//Ref<VertexArray> m_VertexArray;
		//Ref<VertexBuffer> m_VertexBuffer;
		//Ref<IndexBuffer> m_IndexBuffer;
	private:
		static Application* s_Instance;
		friend int ::main(int argc, char** argv);
	};

	// Define in client
	Application* CreateApplication();
}