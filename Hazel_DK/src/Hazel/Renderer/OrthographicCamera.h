#pragma once

#include <glm/glm.hpp>

namespace Hazel
{
	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);
		
		~OrthographicCamera() = default;

		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& position) { RecalculateViewMatrix(); m_Position = position; }

		float GetRotation() const { return m_Rotation; }
		void SetRotation(const float rotation) { RecalculateViewMatrix(); m_Rotation = rotation; }

		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

	private:

		void RecalculateViewMatrix();

		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position;
		float m_Rotation;
	};
}
