#include "qepch.h"
#include "Quest/Utility/PlatformUtility.h"

#include <GLFW/glfw3.h>

namespace Quest
{
	namespace Utility
	{
		float Time::GetTime()
		{
			return glfwGetTime();
		}
	}
}