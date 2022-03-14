#include "hzpch.h"
#include "Texture.h"
#include "Hazel/Core/SystemInfo.h"
#include "Hazel/Platform/OpenGL/OpenGLTexture.h"

namespace Hazel
{
	Ref<Texture2D> Texture2D::Create(const std::string& filepath)
	{
		switch (SystemInfo::GetRenderingAPI())
		{

		case SystemInfo::RenderingAPI::None:
			HZ_CORE_ASSERT(false, "RenderAPI None is not supported!");
			return nullptr;
		case SystemInfo::RenderingAPI::OpenGL:
			return std::make_shared<OpenGLTexture2D>(filepath);

		default:
			HZ_CORE_ASSERT(false, "RenderAPI is not currently supported!");
			return nullptr;
		}
	}
}