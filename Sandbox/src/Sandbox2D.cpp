#include "Sandbox2D.h"

#include "imgui/imgui.h"
#include <glm/glm.hpp>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1920.0f / 1080.0f)
{

}

void Sandbox2D::OnAttach()
{
	m_Texture = Quest::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Quest::Timestep timestep)
{
	QE_PROFILE_FUNCTION();
	// Update
	m_CameraController.OnUpdate(timestep);

	// Render
	Quest::RenderCommand::SetClearColor({ 0.05f, 0.05f, 0.05f, 1.0f });
	Quest::RenderCommand::Clear();

	Quest::Renderer2D::BeginScene(m_CameraController.GetCamera());
	Quest::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	Quest::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
	Quest::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_Texture);
	Quest::Renderer2D::EndScene();

}

void Sandbox2D::OnEvent(Quest::Event& event)
{
	m_CameraController.OnEvent(event);
}

void Sandbox2D::OnImGuiRender()
{

}