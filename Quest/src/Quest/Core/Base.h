#pragma once

#ifdef QE_PLATFORM_WINDOWS

#else
	#error Quest Engine only supports Windows
#endif

#ifdef QE_ENABLE_ASSERTS
	#define QE_ASSERT(x, ...) { if (!(x)) { QE_ERROR("Assert Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define QE_CORE_ASSERT(x, ...) { if (!(x)) { QE_CORE_ERROR("Assert Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define QE_ASSERT(x, ...)
	#define QE_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << (x))

#define QE_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }