#include <Quest.h>

class Sandbox : public Quest::Application {
public:
	Sandbox() {

	}

	~Sandbox() {

	}
};

Quest::Application* Quest::CreateApplication() {
	return new Sandbox();
} 