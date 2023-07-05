#include <Quest.h>

class SandboxLayer : public Quest::Layer
{
public:
	SandboxLayer()
		: Layer("Test Layer")
	{
	}

	void OnUpdate() override
	{
		QE_INFO("SandboxLayer::Update");
	}

	void OnEvent(Quest::Event& event) override
	{
		QE_TRACE("{0}", event);
	}
};

class Sandbox : public Quest::Application {
public:
	Sandbox() {
		//PushLayer(new SandboxLayer());
	}

	~Sandbox() {

	}
};

Quest::Application* Quest::CreateApplication() {
	return new Sandbox();
} 