//A generic Hazel application for testing while developing the Hazel Engine
#include <Hazel.h>
#include "ImGui/imgui.h"

#include "glm/gtc/matrix_transform.hpp"

class TestLayer : public Hazel::Layer
{

public:
	TestLayer()
		: Layer("test layer"), camera({ -1.6f, 1.6f,-0.9f, 0.9f }), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(Hazel::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.0f, 0.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.0f, 0.8f, 0.0f, 1.0f,
			0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.8f, 1.0f
		};

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Hazel::VertexBuffer> VertexBuffer;
		VertexBuffer.reset(Hazel::VertexBuffer::Create(vertices, sizeof(vertices)));

		VertexBuffer->SetLayout({
			{ Hazel::ShaderDataType::Float3, "a_Position" },
			{ Hazel::ShaderDataType::Float4, "a_Color"}
			});

		std::shared_ptr<Hazel::IndexBuffer> IndexBuffer;
		IndexBuffer.reset(Hazel::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		m_VertexArray->AddVertexBuffer(VertexBuffer);
		m_VertexArray->SetIndexBuffer(IndexBuffer);

		m_SquareVA.reset(Hazel::VertexArray::Create());

		float sqVertices[4 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.8f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.8f, 0.8f, 0.8f, 1.0f,
			 0.5f,  0.5f, 0.0f, 0.8f, 0.8f, 0.8f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.8f, 0.8f, 0.8f, 1.0f
		};

		uint32_t sqIndices[6] = { 0, 1, 2, 2, 3, 0 };
		VertexBuffer.reset(Hazel::VertexBuffer::Create(sqVertices, sizeof(sqVertices)));

		VertexBuffer->SetLayout({
			{ Hazel::ShaderDataType::Float3, "a_Position" },
			{ Hazel::ShaderDataType::Float4, "a_Color"}
			});

		IndexBuffer.reset(Hazel::IndexBuffer::Create(sqIndices, sizeof(sqIndices) / sizeof(uint32_t)));

		m_SquareVA->AddVertexBuffer(VertexBuffer);
		m_SquareVA->SetIndexBuffer(IndexBuffer);

		std::string vertSrc = R"(
				#version 330 core
				
				layout(location = 0) in vec3 a_Position;
				layout(location = 1) in vec4 a_Color;

				uniform mat4 u_ViewProjection;
				uniform mat4 u_Transform;

				out vec3 v_Position;
				out vec4 v_Color;

				void main()
				{
					v_Position = a_Position;
					v_Color = a_Color;
					gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
				}
			)";

		std::string fragSrc = R"(
				#version 330 core
				
				layout(location = 0) out vec4 color;
				in vec3 v_Position;
				in vec4 v_Color;

				void main()
				{
					color = vec4(v_Position * 0.5 + 0.5, 1.0);
					color = v_Color;
				}
			)";


		m_Shader.reset(Hazel::Shader::Create(vertSrc, fragSrc));
	}
	
	virtual void OnAttach() override
	{
	
	}
	
	virtual void OnDetach() override
	{
	}
	
	virtual void OnUpdate(Hazel::DeltaTime delta) override
	{

//		HZ_INFO("Delta time is {0}s ({1}milliseconds", delta.GetSeconds(), delta.GetMillis());

		if (Hazel::Input::IsKeyPressed(HZ_KEY_A) || Hazel::Input::IsKeyPressed(HZ_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * delta;
		else if (Hazel::Input::IsKeyPressed(HZ_KEY_D) || Hazel::Input::IsKeyPressed(HZ_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * delta;
		if (Hazel::Input::IsKeyPressed(HZ_KEY_W) || Hazel::Input::IsKeyPressed(HZ_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * delta;
		else if (Hazel::Input::IsKeyPressed(HZ_KEY_S) || Hazel::Input::IsKeyPressed(HZ_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * delta;
		if (Hazel::Input::IsKeyPressed(HZ_KEY_Q))
			m_CameraRotation += m_CameraRotationSpeed * delta;
		else if (Hazel::Input::IsKeyPressed(HZ_KEY_E))
			m_CameraRotation -= m_CameraRotationSpeed * delta;


		camera.SetPosition(m_CameraPosition);
		camera.SetRotation(m_CameraRotation);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		Hazel::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Hazel::RenderCommand::Clear();

		Hazel::Renderer::BeginScene(camera);
		for (int y = 0; y < 20; ++y)
		{
			for (int x = 0; x < 20; ++x)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;

				Hazel::Renderer::Submit(m_SquareVA, m_Shader, transform);
			}
		}

		Hazel::Renderer::Submit(m_VertexArray, m_Shader);

		Hazel::Renderer::EndScene();
	}

	virtual void OnEvent(Hazel::Event& e) override
	{
	}
	virtual void OnImGuiRender() override
	{
//		static bool showdemo = true;
//		ImGui::ShowDemoWindow(&showdemo);
	}

private:
	std::shared_ptr<Hazel::Shader> m_Shader;
	std::shared_ptr<Hazel::VertexArray> m_VertexArray;
	std::shared_ptr<Hazel::VertexArray> m_SquareVA;

	Hazel::OrthographicCamera camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 4.0f;
	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;

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