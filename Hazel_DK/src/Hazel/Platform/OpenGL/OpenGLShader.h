#pragma once
#include <string>
#include "Hazel/Renderer/Shader.h"

namespace Hazel
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertSrc, const std::string& fragSrc);
		~OpenGLShader();

		void Bind() const;
		void UnBind() const;

	private:
		uint32_t m_RendererId;
	};
}