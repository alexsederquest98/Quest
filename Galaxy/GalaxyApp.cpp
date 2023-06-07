#include <Quasar.h>

class Galaxy : public Quasar::Application {
public:
	Galaxy() {

	}

	~Galaxy() {

	}
};

Quasar::Application* Quasar::CreateApplication() {
	return new Galaxy();
} 