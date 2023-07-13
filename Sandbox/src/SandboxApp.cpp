#include <Quest.h>
#include <Quest/Core/EntryPoint.h>

#include "Sandbox2D.h"

#include "imgui/imgui.h"

class SandboxLayer : public Quest::Layer
{
public:
	SandboxLayer()
		: Layer("Test Layer"), m_CameraController(1920.0f / 1080.0f)
	{

		float vertices[] = {
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f, // top right
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f  // top left 
		};

		unsigned int indices[] = { 0, 1, 3, 1, 2, 3 };

		// Setup the vertex array
		m_VertexArray = Quest::VertexArray::Create();

		// Setup vertex buffer
		m_VertexBuffer = Quest::VertexBuffer::Create(vertices, sizeof(vertices));
		Quest::BufferLayout layout = {
			{ Quest::ShaderDataType::Float3, "a_Position" },
			{ Quest::ShaderDataType::Float2, "a_TexCoord" }
		};
		m_VertexBuffer->SetLayout(layout);

		// Setup the index buffer
		m_IndexBuffer = Quest::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

		// Populate vertex array
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		m_TextureShader = Quest::Shader::Create("assets/shaders/Texture.glsl");
		//m_TextureShader = Quest::Shader::Create("Texture", "assets/shaders/Texture.vert", "assets/shaders/Texture.frag");

		m_Texture = Quest::Texture2D::Create("assets/textures/Checkerboard.png");

		m_TextureShader->Bind();
		m_TextureShader->SetInt("u_Texture", 0);
	}

	void OnUpdate(Quest::Timestep timestep) override
	{
		//QE_TRACE("Delta time: {0}", timestep.GetMiliseconds());
		
		// Update
		m_CameraController.OnUpdate(timestep);

		// Render
		Quest::RenderCommand::SetClearColor({ 0.05f, 0.05f, 0.05f, 1.0f });
		Quest::RenderCommand::Clear();

		Quest::Renderer::BeginScene(m_CameraController.GetCamera());

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		glm::vec4 redColor(0.8f, 0.2f, 0.3f, 1.0f);
		glm::vec4 blueColor(0.2f, 0.3f, 0.8f, 1.0f);


		/*for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Quest::Renderer::Submit(m_Shader, m_VertexArray, transform);
			}
		}*/


		m_Texture->Bind();
		Quest::Renderer::Submit(m_TextureShader, m_VertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		Quest::Renderer::EndScene();
	}

	void OnEvent(Quest::Event& event) override
	{
		m_CameraController.OnEvent(event);
	}

	virtual void OnImGuiRender() override
	{
	}
private:
	Quest::Ref<Quest::Shader> m_Shader;
	Quest::Ref<Quest::Shader> m_TextureShader;
	Quest::Ref<Quest::VertexArray> m_VertexArray;
	Quest::Ref<Quest::VertexBuffer> m_VertexBuffer;
	Quest::Ref<Quest::IndexBuffer> m_IndexBuffer;

	Quest::Ref<Quest::Texture2D> m_Texture;

	Quest::OrthographicCameraController m_CameraController;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f};
};

class Sandbox : public Quest::Application {
public:
	Sandbox() {
		//PushLayer(new SandboxLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox() {

	}
};

Quest::Application* Quest::CreateApplication() {
	return new Sandbox();
} 