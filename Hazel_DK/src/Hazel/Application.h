#pragma once
// Hazel applications will inherit from this class to create and run the application on the hazel engine
#include "Core.h"
#include "Window.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Hazel/LayerStack.h"
#include "Hazel/ImGui/ImGuiLayer.h"

#include "Hazel/Core/Time.h"

namespace Hazel {
	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		Ref<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		Ref<Time> m_Time;
		float m_LastFrameComplete;

		static Application* s_Instance;
	};

	Application* CreateApplication(); //to be implemented by Hazel Client Applications
}
