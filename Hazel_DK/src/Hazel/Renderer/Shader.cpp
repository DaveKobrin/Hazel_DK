#include "hzpch.h"
#include "Shader.h"

#include "Hazel/Core/SystemInfo.h"
//#include "Hazel/Renderer/Renderer.h"
#include "Hazel/Platform/OpenGL/OpenGLShader.h"

namespace Hazel
{
	Shader* Shader::Create(const std::string& vertSrc, const std::string& fragSrc)
	{
		{
			switch (SystemInfo::GetRenderingAPI())
			{

			case SystemInfo::RenderingAPI::None:
				HZ_CORE_ASSERT(false, "RenderAPI None is not supported!");
				return nullptr;
			case SystemInfo::RenderingAPI::OpenGL:
				return new OpenGLShader(vertSrc, fragSrc);

			default:
				HZ_CORE_ASSERT(false, "RenderAPI is not currently supported!");
				return nullptr;
			}
		};
	}
}