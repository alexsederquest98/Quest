#include "qepch.h"
#include "Quest/Core/Window.h"

#ifdef QE_PLATFORM_WINDOWS
	#include "Quest/Platform/Windows/WindowsWindow.h"
#endif

namespace Quest
{
	Scope<Window> Window::Create(const WindowProperties& props)
	{
	#ifdef QE_PLATFORM_WINDOWS
		return CreateScope<WindowsWindow>(props);
	#else
		QE_CORE_ASSERT(false, "Unknown platform");
		return nullptr;
	#endif
	}
}