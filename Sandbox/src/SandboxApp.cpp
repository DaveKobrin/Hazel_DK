//A generic Hazel application for testing while developing the Hazel Engine
#include <Hazel.h>


class Sandbox : public Hazel::Application
{
public:
	Sandbox() {}
	~Sandbox() {}
};

Hazel::Application* Hazel::CreateApplication() {
	return new Sandbox;
}