#pragma once
#include <qepch.h>
#include "Quest/Core/Application.h"

extern Quest::Application* Quest::CreateApplication();

int main(int argc, char** argv)
{
	std::cout << "Quest Engine Initializing..." << std::endl;

	Quest::Logger::Init();
	QE_CORE_INFO("Initialized Engine Log.");
	QE_INFO("Initialized Client Log.");

	QE_PROFILE_BEGIN_SESSION("Startup", "QuestProfile-Startup.json");
	auto app = Quest::CreateApplication();
	QE_PROFILE_END_SESSION();

	QE_PROFILE_BEGIN_SESSION("Runtime", "QuestProfile-Runtime.json");
	app->Run();
	QE_PROFILE_END_SESSION();

	QE_PROFILE_BEGIN_SESSION("Shutdown", "QuestProfile-Shutdown.json");
	delete app;
	QE_PROFILE_END_SESSION();
}
