#pragma once
#include <qspch.h>
#include "Quasar/Core/Application.h"

extern Quasar::Application* Quasar::CreateApplication();

int main(int argc, char** argv)
{
	std::cout << "Quasar Engine Initializing..." << std::endl;

	Quasar::Logger::Init();
	QS_CORE_INFO("Initialized Engine Log.");
	QS_INFO("Initialized Client Log.");

	auto app = Quasar::CreateApplication();
	app->Run();
	delete app;
}
