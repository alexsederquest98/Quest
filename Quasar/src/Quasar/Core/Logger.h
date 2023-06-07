#pragma once

#include "Quasar/Core/Base.h"
#pragma warning(push, 0)
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"
#pragma warning(pop)

namespace Quasar
{

	class Logger
	{
	public:
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Macros for engine logger for ease of use
#define QS_CORE_TRACE(...) ::Quasar::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define QS_CORE_INFO(...)  ::Quasar::Log::GetCoreLogger()->info(__VA_ARGS__)
#define QS_CORE_WARN(...)  ::Quasar::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define QS_CORE_ERROR(...) ::Quasar::Log::GetCoreLogger()->error(__VA_ARGS__)
//#define QS_CORE_FATAL(...) ::Quasar::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Macros for client logger for ease of use
#define QS_TRACE(...) ::Quasar::Log::GetClientLogger()->trace(__VA_ARGS__)
#define QS_INFO(...)  ::Quasar::Log::GetClientLogger()->info(__VA_ARGS__)
#define QS_WARN(...)  ::Quasar::Log::GetClientLogger()->warn(__VA_ARGS__)
#define QS_ERROR(...) ::Quasar::Log::GetClientLogger()->error(__VA_ARGS__)
//#define QS_FATAL(...) ::Quasar::Log::GetClientLogger()->fatal(__VA_ARGS__)