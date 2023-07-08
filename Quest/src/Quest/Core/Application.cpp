#include "qepch.h"

#include "Quest/Core/Application.h"
//#include "Quest/Events/ApplicationEvent.h"
#include "Quest/Core/Logger.h"

#include "Quest/Renderer/Renderer.h"

namespace Quest
{
	Application* Application::s_Instance = nullptr;

	#define BIND_EVENT_CALLBACK(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application()
	{
		// TRIANGLE TEST
		renderShape = 1;

		s_Instance = this;

		m_Window = Window::Create();
		m_Window->SetEventCallback(BIND_EVENT_CALLBACK(OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		// Setup Triangle Test
		switch (renderShape)
		{
		case 0: SetupAPITriangle(); break;
		case 1: SetupAPIRect(); break;
		}
	}

	void Application::SetupAPITriangle()
	{
		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		unsigned int indices[3] = { 0, 1, 2 };

		// Setup the vertex array
		m_VertexArray = VertexArray::Create();

		// Setup vertex buffer
		m_VertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
		BufferLayout layout = {
			{ ShaderDataType::Vec3, "a_Position" }
		};
		m_VertexBuffer->SetLayout(layout);

		// Setup the index buffer
		m_IndexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

		// Populate vertex array
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		std::string vsrc = R"(
			#version 460 core
			layout (location = 0) in vec3 a_Position;
			//layout (location = 1) in vec4 a_Color;
			
			out vec3 v_Position;
			//out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				//v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";


		std::string fSrc = R"(
			#version 460 core
			layout(location = 0) out vec4 color;
			
			in vec3 v_Position;
			//in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				//color = v_Color;
			}
		)";

		m_Shader = Shader::Create("Triangle", vsrc, fSrc);
	}

	void Application::SetupAPIRect()
	{
		m_VertexArray = VertexArray::Create();

		float vertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f

		};

		unsigned int indices[6] = { 0, 1, 2, 2, 3, 0 };

		m_VertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
		BufferLayout layout = {
			{ ShaderDataType::Vec3, "a_Position" }
		};
		m_VertexBuffer->SetLayout(layout);

		// Setup the index buffer
		m_IndexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

		// Populate vertex array
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		std::string vsrc = R"(
			#version 460 core
			layout (location = 0) in vec3 a_Position;
			
			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";


		std::string fSrc = R"(
			#version 460 core
			layout(location = 0) out vec4 color;
			
			in vec3 v_Position;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
			}
		)";

		m_Shader = Shader::Create("Rect", vsrc, fSrc);
	}

	Application::~Application()
	{
		//m_ImGuiLayer->OnDetach();
	}

	void Application::Run()
	{
		while (m_Running)
		{
			RenderCommand::SetClearColor({ 0.05f, 0.05f, 0.05f, 1.0f });
			RenderCommand::Clear();

			Renderer::BeginScene();

			Renderer::Submit(m_Shader, m_VertexArray);
			
			Renderer::EndScene();

			// Update layers
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			// Update ImGui layer
			m_ImGuiLayer->BeginFrame();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->EndFrame();

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