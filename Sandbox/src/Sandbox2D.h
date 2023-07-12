#pragma once

#include <Quest.h>

class Sandbox2D : public Quest::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;
	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(Quest::Timestep timestep) override;
	virtual void OnEvent(Quest::Event& event) override;
	virtual void OnImGuiRender() override;
private:
	Quest::OrthographicCameraController m_CameraController;

	Quest::Ref<Quest::VertexBuffer> m_VertexBuffer;
	Quest::Ref<Quest::IndexBuffer> m_IndexBuffer;
	Quest::Ref<Quest::VertexArray> m_VertexArray;
	Quest::Ref<Quest::Shader> m_Shader;
	
	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};