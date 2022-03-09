#include "hzpch.h"
#include "Shader.h"

#include "Hazel/Renderer/Renderer.h"
#include "Hazel/Platform/OpenGL/OpenGLShader.h"

namespace Hazel
{
	Shader* Shader::Create(const std::string& vertSrc, const std::string& fragSrc)
	{
		{
			switch (Renderer::GetAPI())
			{

			case RendererAPI::API::None:
				HZ_CORE_ASSERT(false, "RenderAPI None is not supported!");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return new OpenGLShader(vertSrc, fragSrc);

			}

			HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		};
	}
}