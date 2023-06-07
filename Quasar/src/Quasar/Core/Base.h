#pragma once

#ifdef QS_PLATFORM_WINDOWS

#else
	#error Quasar Engine only supports Windows
#endif

#ifdef QS_ENABLE_ASSERTS
	#define QS_ASSERT(x, ...) { if (!(x)) { QS_ERROR("Assert Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define QS_CORE_ASSERT(x, ...) { if (!(x)) { QS_CORE_ERROR("Assert Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define QS_ASSERT(x, ...)
	#define QS_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << (x))

#define QS_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }