#include <Quest.h>

#include "imgui/imgui.h"

class SandboxLayer : public Quest::Layer
{
public:
	SandboxLayer()
		: Layer("Test Layer"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		unsigned int indices[3] = { 0, 1, 2 };

		// Setup the vertex array
		m_VertexArray = Quest::VertexArray::Create();

		// Setup vertex buffer
		m_VertexBuffer = Quest::VertexBuffer::Create(vertices, sizeof(vertices));
		Quest::BufferLayout layout = {
			{ Quest::ShaderDataType::Vec3, "a_Position" }
		};
		m_VertexBuffer->SetLayout(layout);

		// Setup the index buffer
		m_IndexBuffer = Quest::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

		// Populate vertex array
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		std::string vsrc = R"(
			#version 460 core
			layout (location = 0) in vec3 a_Position;
			//layout (location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;			

			out vec3 v_Position;
			//out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				//v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
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

		m_Shader = Quest::Shader::Create("Triangle", vsrc, fSrc);
	}

	void OnUpdate() override
	{
		//QE_TRACE("{0}", counter);
		Quest::RenderCommand::SetClearColor({ 0.05f, 0.05f, 0.05f, 1.0f });
		Quest::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(0);

		Quest::Renderer::BeginScene(m_Camera);

		Quest::Renderer::Submit(m_Shader, m_VertexArray);

		Quest::Renderer::EndScene();
	}

	void OnEvent(Quest::Event& event) override
	{
		Quest::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<Quest::KeyPressedEvent>(QE_BIND_EVENT_FN(SandboxLayer::OnKeyPressedEvent));
	}

	bool OnKeyPressedEvent(Quest::KeyPressedEvent& event)
	{
		if (Quest::Input::IsKeyPressed(Quest::Key::Left))
			m_CameraPosition.x -= m_CameraSpeed;
		if (Quest::Input::IsKeyPressed(Quest::Key::Right))
			m_CameraPosition.x += m_CameraSpeed;
		if (Quest::Input::IsKeyPressed(Quest::Key::Down))
			m_CameraPosition.y -= m_CameraSpeed;
		if (Quest::Input::IsKeyPressed(Quest::Key::Up))
			m_CameraPosition.y += m_CameraSpeed;

		if (event.GetEventType() == Quest::EventType::KeyPressed)
		{
			Quest::KeyPressedEvent& e = (Quest::KeyPressedEvent&)event;
			QE_TRACE("{0}", (char)e.GetKeyCode());
		}

		return false;
	}

	virtual void OnImGuiRender() override
	{
	}
private:
	Quest::Ref<Quest::Shader> m_Shader;
	Quest::Ref<Quest::VertexArray> m_VertexArray;
	Quest::Ref<Quest::VertexBuffer> m_VertexBuffer;
	Quest::Ref<Quest::IndexBuffer> m_IndexBuffer;
	Quest::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraSpeed = 0.1f;
};

class Sandbox : public Quest::Application {
public:
	Sandbox() {
		PushLayer(new SandboxLayer());
		//PushLayer(new InputLayerTest());
	}

	~Sandbox() {

	}
};

Quest::Application* Quest::CreateApplication() {
	return new Sandbox();
} 