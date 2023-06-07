#pragma once
#include <qspch.h>
#include "Application.h"

extern Quasar::Application* Quasar::CreateApplication();

int main(int argc, char** argv)
{
	std::cout << "Quest Engine Initializing..." << std::endl;

	Quasar::Log::Init();
	QS_CORE_INFO("Initialized Engine Log.");
	QS_INFO("Initialized Client Log.");

	auto app = Quasar::CreateApplication();
	app->Run();
	delete app;
}
