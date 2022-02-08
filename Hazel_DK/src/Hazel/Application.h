#pragma once
// Hazel applications will inherit from this class to create and run the application on the hazel engine
#include "Core.h"
#include "Window.h"
#include "Events/Event.h"

namespace Hazel {
	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	Application* CreateApplication(); //to be implemented by Hazel Client Applications
}
