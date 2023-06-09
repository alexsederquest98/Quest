#pragma once

#include "Quest/Core/KeyCodes.h"
#include "Quest/Core/MouseCodes.h"

#include <glm/glm.hpp>

namespace Quest
{
	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);
		static bool IsMouseButtonPressed(MouseCode button);
		static glm::vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}