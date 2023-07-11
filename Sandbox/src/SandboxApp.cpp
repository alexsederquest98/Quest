#include <Quest.h>

#include "imgui/imgui.h"

class SandboxLayer : public Quest::Layer
{
public:
	SandboxLayer()
		: Layer("Test Layer"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f, 0.0f, 0.0f), m_SquarePos(0.0f)
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
			{ Quest::ShaderDataType::Vec3, "a_Position" },
			{ Quest::ShaderDataType::Vec2, "a_TexCoord" }
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

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;			

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";


		std::string fSrc = R"(
			#version 460 core
			layout(location = 0) out vec4 color;
			
			in vec3 v_Position;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		std::string textureShaderVSrc = R"(
			#version 460 core
			layout (location = 0) in vec3 a_Position;
			layout (location = 1) in vec2 a_TexCoord;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;			

			out vec2 v_TexCoord;

			void main()
			{
				v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";


		std::string textureShaderFSrc = R"(
			#version 460 core
			layout(location = 0) out vec4 color;
			
			in vec2 v_TexCoord;

			uniform sampler2D u_Texture;

			void main()
			{
				color = texture(u_Texture, v_TexCoord);
			}
		)";

		m_Shader = Quest::Shader::Create("Square", vsrc, fSrc);
		m_TextureShader = Quest::Shader::Create("Texture", textureShaderVSrc, textureShaderFSrc);

		m_Texture = Quest::Texture2D::Create("assets/textures/Checkerboard.png");

		m_TextureShader->Bind();
		m_TextureShader->SetInt("u_Texture", 0);
	}

	void OnUpdate(Quest::Timestep timestep) override
	{
		//QE_TRACE("Delta time: {0}", timestep.GetMiliseconds());

		if (Quest::Input::IsKeyPressed(Quest::Key::Left))
			m_CameraPosition.x -= m_CameraSpeed * timestep;
		else if (Quest::Input::IsKeyPressed(Quest::Key::Right))
			m_CameraPosition.x += m_CameraSpeed * timestep;
		if (Quest::Input::IsKeyPressed(Quest::Key::Up))
			m_CameraPosition.y += m_CameraSpeed * timestep;
		else if (Quest::Input::IsKeyPressed(Quest::Key::Down))
			m_CameraPosition.y -= m_CameraSpeed * timestep;

		if (Quest::Input::IsKeyPressed(Quest::Key::A))
			m_CameraRotation += m_CameraRotationSpeed * timestep;
		if (Quest::Input::IsKeyPressed(Quest::Key::D))
			m_CameraRotation -= m_CameraRotationSpeed * timestep;

		Quest::RenderCommand::SetClearColor({ 0.05f, 0.05f, 0.05f, 1.0f });
		Quest::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Quest::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		glm::vec4 redColor(0.8f, 0.2f, 0.3f, 1.0f);
		glm::vec4 blueColor(0.2f, 0.3f, 0.8f, 1.0f);

		m_Shader->Bind();
		m_Shader->SetVec3("u_Color", m_SquareColor);

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
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Color Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}
private:
	Quest::Ref<Quest::Shader> m_Shader;
	Quest::Ref<Quest::Shader> m_TextureShader;
	Quest::Ref<Quest::VertexArray> m_VertexArray;
	Quest::Ref<Quest::VertexBuffer> m_VertexBuffer;
	Quest::Ref<Quest::IndexBuffer> m_IndexBuffer;

	Quest::Ref<Quest::Texture2D> m_Texture;

	Quest::OrthographicCamera m_Camera;

	glm::vec3 m_CameraPosition;
	float m_CameraSpeed = 1.0f;
	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 10.0f;
	glm::vec3 m_SquarePos;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f};
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