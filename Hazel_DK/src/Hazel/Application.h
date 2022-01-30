#pragma once
// Hazel applications will inherit from this class to create and run the application on the hazel engine
#include "Core.h"

namespace Hazel {
	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};


	Application* CreateApplication(); //to be implemented by Hazel Client Applications
}
