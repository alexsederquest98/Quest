#pragma once

#include "Quest/Core/Base.h"
#pragma warning(push, 0)
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"
#pragma warning(pop)

namespace Quest
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
#define QE_CORE_TRACE(...) ::Quest::Logger::GetCoreLogger()->trace(__VA_ARGS__)
#define QE_CORE_INFO(...)  ::Quest::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define QE_CORE_WARN(...)  ::Quest::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define QE_CORE_ERROR(...) ::Quest::Logger::GetCoreLogger()->error(__VA_ARGS__)
//#define QE_CORE_FATAL(...) ::Quest::Logger::GetCoreLogger()->fatal(__VA_ARGS__)

// Macros for client logger for ease of use
#define QE_TRACE(...) ::Quest::Logger::GetClientLogger()->trace(__VA_ARGS__)
#define QE_INFO(...)  ::Quest::Logger::GetClientLogger()->info(__VA_ARGS__)
#define QE_WARN(...)  ::Quest::Logger::GetClientLogger()->warn(__VA_ARGS__)
#define QE_ERROR(...) ::Quest::Logger::GetClientLogger()->error(__VA_ARGS__)
//#define QE_FATAL(...) ::Quest::Logger::GetClientLogger()->fatal(__VA_ARGS__)