#include "qepch.h"
#include "Quest/Core/Input.h"
#include "Quest/Core/Application.h"
#include <GLFW/glfw3.h>

namespace Quest
{
	bool Input::IsKeyPressed(const KeyCode key)
	{
		auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetWindow());
		auto keyState = glfwGetKey(window, static_cast<int32_t>(key));
		return keyState == GLFW_PRESS;
	}

	bool Input::IsMouseButtonPressed(const MouseCode button)
	{
		auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetWindow());
		auto mouseState = glfwGetMouseButton(window, static_cast<int32_t>(button));
		return mouseState == GLFW_PRESS;
	}

	glm::vec2 Input::GetMousePosition()
	{
		auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}

	float Input::GetMouseX()
	{
		return GetMousePosition().x;
	}

	float Input::GetMouseY()
	{
		return GetMousePosition().y;
	}
}