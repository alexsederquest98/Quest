#pragma once

#include "Quest/Core/Base.h"
#include "Quest/Events/Event.h"

#include "Quest/Renderer/RenderingContext.h"

#include <GLFW/glfw3.h>
#include <string>

namespace Quest
{
	struct WindowProperties
	{
		std::string title;
		uint32_t width;
		uint32_t height;

		WindowProperties(const std::string& _title = "Quest Engine", uint32_t  _width = 1920, uint32_t _height = 1080)
			: title(_title), width(_width), height(_height)
		{
		}
	};

	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;
		
		Window(const WindowProperties& props);
		~Window();
		
		void OnUpdate();

		inline uint32_t GetWidth() { return m_Data.width; }
		inline uint32_t GetHeight() { return m_Data.height; }

		void SetEventCallback(const EventCallbackFn& callback) { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled);
		bool IsVSync() { return m_Data.vsync; };
	private:
		void Init(const WindowProperties& props);
		void Shutdown();
		
	private:
		GLFWwindow* m_Window;
		Scope<RenderingContext> m_Context;

		struct WindowData
		{
			std::string title;
			uint32_t width;
			uint32_t height;
			bool vsync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;

	};
}