#include "qepch.h"

#include "Quest/Core/Application.h"
//#include "Quest/Events/ApplicationEvent.h"
#include "Quest/Core/Logger.h"

#include "Quest/Renderer/Renderer.h"
#include "Quest/Utility/PlatformUtility.h"

namespace Quest
{
	Application* Application::s_Instance = nullptr;

	#define BIND_EVENT_CALLBACK(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application()
	{
		s_Instance = this;

		m_Window = Window::Create();
		m_Window->SetEventCallback(BIND_EVENT_CALLBACK(OnEvent));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{
		//m_ImGuiLayer->OnDetach();
	}

	void Application::Run()
	{
		QE_PROFILE_FUNCTION();
		while (m_Running)
		{
			// Frame time stuff
			float time = Utility::Time::GetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			// Run the updates if the window is not minimized
			if (!m_Minimized)
			{
				// Update layers
				for (Layer* layer : m_LayerStack)
					layer->OnUpdate(timestep);

				// Update ImGui layer
				m_ImGuiLayer->BeginFrame();
				for (Layer* layer : m_LayerStack)
					layer->OnImGuiRender();
				m_ImGuiLayer->EndFrame();
			}

			m_Window->OnUpdate();
		}
	}

	void Application::Close()
	{
		m_Running = false;
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		//QE_CORE_INFO("{0}", e);

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_CALLBACK(OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_CALLBACK(OnWindowResize));

		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
		{
			if (e.Handled)
				break;
			(*it)->OnEvent(e);
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}
}