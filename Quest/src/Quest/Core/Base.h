#pragma once

#include <memory>

#ifdef _WIN32
	#ifdef _WIN64
		#define QE_PLATFORM_WINDOWS
	#endif
#endif


#ifdef QE_PLATFORM_WINDOWS

#else
	#error Quest Engine only supports Windows
#endif

#ifdef QE_DEBUG
	#if defined(QE_PLATFORM_WINDOWS)
		#define QE_DEBUGBREAK() __debugbreak()
	#else
		#error "Platform doesn't support debugbreak yet"
	#endif
	
	#define QE_ENABLE_ASSERTS
#else
	#define QE_DEBUGBREAK()
#endif

#define QE_EXPAND_MACRO(x) x
#define QE_STRINGIFY_MACRO(x) #x

#define BIT(x) (1 << (x))

#define QE_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

// Adding some typedefs for stuff I may want to replace with custom implementations later on
namespace Quest
{
	// Scope is a std::unique_ptr but I can change how its implemented later on as needs change
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	// Ref is a std::shared_ptr but I can change how its implemented later on as needs change
	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	//template<typename T1, typename T2>
	//using DynamicPointerCast = std::dynamic_pointer_cast<T1>(T2);
}

// Down here to deal with some circular includes in Assert.h
#include "Quest/Core/Logger.h"
#include "Quest/Core/Assert.h"