#pragma once

#include "Quasar/Core/Base.h"
#include "Quasar/Events/ApplicationEvent.h"

namespace Quasar
{

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// Define in client
	Application* CreateApplication();
}