#pragma once

#include <string>
#include <chrono>
#include <fstream>
#include <algorithm>
#include <thread>

namespace Quest
{
	namespace Utility
	{
		class Instrumentor
		{

		};

		class InstrumentorTimer
		{

		};

	}
}

#define QE_PROFILING 0
#if QE_PROFILING
	#define QE_PROFILE_BEGIN_SESSION(name, filepath) ::Quest::Utility::Instrumentor::Get().BeginSession(name, filepath)
	#define QE_PROFILE_END_SESSION() ::Quest::Utility::Instrumentor::Get().EndSession()
	#define QE_PROFILE_SCOPE(name) ::Quest::Utility::InstrumentorTimer timer##__LINE__(name);
	#define QE_PROFILE_FUNCTION() QE_PROFILE_SCOPE(__FUNCSIG__)
#else
	#define QE_PROFILE_BEGIN_SESSION(name, filepath)
	#define QE_PROFILE_END_SESSION()
	#define QE_PROFILE_SCOPE(name)
	#define QE_PROFILE_FUNCTION()
#endif