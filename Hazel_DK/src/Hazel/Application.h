#pragma once
// Hazel applications will inherit from this class to create and run the application on the hazel engine
#include "Core.h"
#include "Window.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Hazel/LayerStack.h"
#include "Hazel/ImGui/ImGuiLayer.h"

#include "Hazel/Renderer/Shader.h"
#include "Hazel/Renderer/VertexArray.h"
#include "Hazel/Renderer/Buffer.h"

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
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;


		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;
		std::shared_ptr<VertexArray> m_SquareVA;


		static Application* s_Instance;
	};

	Application* CreateApplication(); //to be implemented by Hazel Client Applications
}
