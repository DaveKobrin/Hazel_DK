// Hazel applications will inherit from this class to create and run the application on the hazel engine
#include "Application.h"

#include "Hazel/Events/ApplicationEvent.h"
#include "Log.h"

#include <iostream>

namespace Hazel {
	Application::Application() {

	}
	Application::~Application() {

	}

	void Application::Run() {
		long count = 0;
		WindowResizeEvent e(1280, 720);
		HZ_TRACE(e.ToString());

		while (true)
		{
			count++;
		}
	}
}