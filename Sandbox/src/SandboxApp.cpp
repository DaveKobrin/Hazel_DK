//A generic Hazel application for testing while developing the Hazel Engine
#include <Hazel.h>


class TestLayer : public Hazel::Layer
{
public:
	TestLayer()
		: Layer("test layer") {}

	void OnUpdate() override
	{
		HZ_INFO("TestLayer::OnUpdate");
	}

	void OnEvent(Hazel::Event& e) override
	{
		HZ_TRACE("{0}", e);
	}
};


class Sandbox : public Hazel::Application
{
public:
	Sandbox() 
	{
		PushLayer(new TestLayer());
	}
	~Sandbox() {}
};

Hazel::Application* Hazel::CreateApplication() {
	return new Sandbox;
}