#include "qepch.h"

#include "Quest/Core/Application.h"
//#include "Quest/Events/ApplicationEvent.h"
#include "Quest/Core/Logger.h"

#include <glad/glad.h>

namespace Quest
{
	Application* Application::s_Instance = nullptr;

	#define BIND_EVENT_CALLBACK(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application()
	{
		s_Instance = this;

		m_Window = new Window(WindowProperties());
		m_Window->SetEventCallback(BIND_EVENT_CALLBACK(OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		m_ImGuiLayer->OnAttach();
		//PushOverlay(m_ImGuiLayer);

		// Triangle Testing Code
		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		glGenBuffers(1, &m_VertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		glGenBuffers(1, &m_IndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);

		unsigned int indices[3] = { 0, 1, 2 };
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		/*m_VertexArray = VertexArray::Create();
		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};
		
		m_VertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
		BufferLayout layout = {
			{ ShaderDataType::Vec3, "a_Position" },
			{ ShaderDataType::Vec4, "a_Color" }
		};
		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		m_IndexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);*/

		//std::string vertexSrc = R"(
		//	#version 330 core

		//	layout(location = 0) in vec3 a_Position;
		//	layout(location = 1) in vec4 a_Color;

		//	out vec3 v_Position;
		//	out vec4 v_Color;

		//	void main()
		//	{
		//		v_Position = a_Position;
		//		v_Color = a_Color;
		//		gl_Position = vec4(a_Position, 1.0);
		//	}
		//)";

		//std::string fragmentSrc = R"(
		//	#version 330 core
		//	layout(location = 0) out vec4 color;
		//	in vec3 v_Position;
		//	in vec4 v_Color;
		//	void main()
		//	{
		//		color = vec4(v_Position * 0.5 + 0.5, 1.0);
		//		color = v_Color;
		//	}
		//)";

		//m_Shader = Shader::Create("Triangle", vertexSrc, fragmentSrc);
	}

	Application::~Application()
	{
		m_ImGuiLayer->OnDetach();
		delete m_Window;
	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(0.05f, 0.05f, 0.05f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			//m_Shader->Bind();
			//m_VertexArray->Bind();

			glBindVertexArray(m_VertexArray);

			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

			// Update layers
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			// Update ImGui layer
			m_ImGuiLayer->BeginFrame();
			m_ImGuiLayer->OnUpdate();
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