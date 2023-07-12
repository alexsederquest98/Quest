#pragma once

#include "Quest/Core/Base.h"
#include "Quest/Events/Event.h"

#include "Quest/Renderer/RenderingContext.h"

#include <string>

namespace Quest
{
	struct WindowProperties
	{
		std::string title;
		uint32_t width;
		uint32_t height;

		WindowProperties(const std::string& _title = "Quest Engine",
			uint32_t  _width = 1920, 
			uint32_t _height = 1080)
			: title(_title), width(_width), height(_height)
		{
		}
	};

	// Window interface
	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;
		
		virtual void OnUpdate() = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;
		static Scope<Window> Create(const WindowProperties& props = WindowProperties());	
	};
}