#include "Sandbox2D.h"

#include "imgui/imgui.h"
#include <glm/glm.hpp>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1920.0f / 1080.0f)
{

}

void Sandbox2D::OnAttach()
{
	float vertices[] = {
			 0.5f,  0.5f, 0.0f, // top right
			 0.5f, -0.5f, 0.0f, // bottom right
			-0.5f, -0.5f, 0.0f, // bottom left
			-0.5f,  0.5f, 0.0f  // top left 
	};

	unsigned int indices[] = { 0, 1, 3, 1, 2, 3 };

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

	m_Shader = Quest::Shader::Create("assets/shaders/FlatColorShader.glsl");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Quest::Timestep timestep)
{
	// Update
	m_CameraController.OnUpdate(timestep);

	// Render
	Quest::RenderCommand::SetClearColor({ 0.05f, 0.05f, 0.05f, 1.0f });
	Quest::RenderCommand::Clear();

	Quest::Renderer::BeginScene(m_CameraController.GetCamera());

	m_Shader->Bind();
	m_Shader->SetVec4("u_Color", m_SquareColor);

	Quest::Renderer::Submit(m_Shader, m_VertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	Quest::Renderer::EndScene();

}

void Sandbox2D::OnEvent(Quest::Event& event)
{
	m_CameraController.OnEvent(event);
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Square Color Settings");
	ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}