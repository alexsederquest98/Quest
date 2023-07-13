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

	Quest::Renderer2D::ResetStats();

	// Render
	Quest::RenderCommand::SetClearColor({ 0.05f, 0.05f, 0.05f, 1.0f });
	Quest::RenderCommand::Clear();

	static float rotation = 0.0f;
	rotation += timestep * 50.0f;

	/*Quest::Renderer2D::BeginScene(m_CameraController.GetCamera());
	Quest::Renderer2D::DrawRotatedQuad({ 1.0f, 0.0f }, { 0.8f, 0.8f }, -45.0f, { 0.8f, 0.2f, 0.3f, 1.0f });
	Quest::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	Quest::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
	Quest::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_Texture, 10.0f);
	Quest::Renderer2D::DrawRotatedQuad({ -2.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, rotation, m_Texture, 20.0f);
	Quest::Renderer2D::EndScene();*/

	Quest::Renderer2D::BeginScene(m_CameraController.GetCamera());
	for (float y = -10.0f; y < 10.0f; y += 0.5f)
	{
		for (float x = -10.0f; x < 10.0f; x += 0.5f)
		{
			glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };
			Quest::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
		}
	}
	Quest::Renderer2D::EndScene();

}

void Sandbox2D::OnEvent(Quest::Event& event)
{
	m_CameraController.OnEvent(event);
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Statistics");

	auto stats = Quest::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

	ImGui::End();
}