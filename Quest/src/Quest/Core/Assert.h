#pragma once

#include "Quest/Core/Base.h"
#include "Quest/Core/Logger.h"

#ifdef QE_ENABLE_ASSERTS
	#define QE_ASSERT(x, ...) { if (!(x)) { QE_ERROR("Assert Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define QE_CORE_ASSERT(x, ...) { if (!(x)) { QE_CORE_ERROR("Assert Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define QE_ASSERT(x, ...)
	#define QE_CORE_ASSERT(x, ...)
#endif