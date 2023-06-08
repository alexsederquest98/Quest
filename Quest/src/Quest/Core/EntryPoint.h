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

	auto app = Quest::CreateApplication();
	app->Run();
	delete app;
}
