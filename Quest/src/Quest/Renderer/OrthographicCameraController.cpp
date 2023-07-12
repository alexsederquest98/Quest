#include "qepch.h"
#include "Quest/Renderer/OrthographicCameraController.h"

#include "Quest/Core/Input.h"

namespace Quest
{
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		: m_AspectRatio(aspectRatio), m_Rotation(rotation), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio* m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel)
	{

	}

	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		if (Input::IsKeyPressed(Quest::Key::A))
			m_CameraPosition.x -= m_CameraTranslationSpeed * ts;
		else if (Quest::Input::IsKeyPressed(Quest::Key::D))
			m_CameraPosition.x += m_CameraTranslationSpeed * ts;
		if (Input::IsKeyPressed(Quest::Key::W))
			m_CameraPosition.y += m_CameraTranslationSpeed * ts;
		else if (Input::IsKeyPressed(Quest::Key::S))
			m_CameraPosition.y -= m_CameraTranslationSpeed * ts;

		if (m_Rotation)
		{
			if (Input::IsKeyPressed(Quest::Key::A))
				m_CameraRotation += m_CameraRotationSpeed * ts;
			if (Input::IsKeyPressed(Quest::Key::D))
				m_CameraRotation -= m_CameraRotationSpeed * ts;

			if (m_CameraRotation > 180.0f)
				m_CameraRotation -= 360.0f;
			else if (m_CameraRotation <= -180.0f)
				m_CameraRotation += 360.0f;

			m_Camera.SetRotation(m_CameraRotation);
		}

		m_Camera.SetPosition(m_CameraPosition);
		m_CameraTranslationSpeed = m_ZoomLevel;
		
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(QE_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(QE_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}

	void OrthographicCameraController::OnResize(float width, float height)
	{
		m_AspectRatio = width / height;
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	}

	OrthographicCamera& OrthographicCameraController::GetCamera() 
	{ 
		return m_Camera; 
	}

	const OrthographicCamera& OrthographicCameraController::GetCamera() const 
	{ 
		return m_Camera;
	}

	float OrthographicCameraController::GetZoomLevel() const 
	{ 
		return m_ZoomLevel;
	}

	void OrthographicCameraController::SetZoomLevel(float level) 
	{ 
		m_ZoomLevel = level;
	}

	bool OrthographicCameraController::GetRotationEnabled() const
	{
		return m_Rotation;
	}

	void OrthographicCameraController::SetRotationEnabled(bool rotation)
	{
		m_Rotation = rotation;
	}

	float OrthographicCameraController::GetRotationDegrees() const
	{
		return m_CameraRotation;
	}

	void OrthographicCameraController::SetRotationDegrees(float degrees)
	{
		m_CameraRotation = degrees;
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= e.GetYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		OnResize((float)e.GetWidth(), (float)e.GetHeight());
		return false;
	}
}