#pragma once

#include "Quest/Renderer/OrthographicCamera.h"
#include "Quest/Core/Timestep.h"
#include "Quest/Events/ApplicationEvent.h"
#include "Quest/Events/MouseEvent.h"

namespace Quest
{
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);
		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);
		void OnResize(float width, float height);
		OrthographicCamera& GetCamera();
		const OrthographicCamera& GetCamera() const;
		float GetZoomLevel() const;
		void SetZoomLevel(float level);
		bool GetRotationEnabled() const;
		void SetRotationEnabled(bool rotation);
		float GetRotationDegrees() const;
		void SetRotationDegrees(float degrees);
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		float m_AspectRatio;
		bool m_Rotation;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f; // degrees in counter-clockwise direction
		float m_CameraTranslationSpeed = 5.0f;
		float m_CameraRotationSpeed = 180.0f;
	};
}