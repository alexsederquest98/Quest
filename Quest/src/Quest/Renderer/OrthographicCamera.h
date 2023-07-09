#pragma once

#include <glm/glm.hpp>

namespace Quest
{
	class OrthographicCamera
	{
	public:
		// Apparently using near and far are #define's for some reason, guessing in glm.hpp, so using n and f respectively
		OrthographicCamera(float left, float right, float bottom, float top, float n = -1.0f, float f = 1.0f);

		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
		const glm::vec3& GetPosition() const { return m_Position; }
		float GetRotation() const { return m_Rotation; }

		void SetPosition(const glm::vec3& pos);
		void SetRotation(float rot);
		void SetProjection(float left, float right, float bottom, float top, float n = -1.0f, float f = 1.0f);
	private:
		void RecalculateViewProjectionMatrix();
	private:
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position{ 0.0f, 0.0f, 0.0f };
		float m_Rotation = 0.0f;
	};
}