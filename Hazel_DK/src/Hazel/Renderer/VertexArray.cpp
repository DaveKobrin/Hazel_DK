#include "hzpch.h"
#include "VertexArray.h"

#include "Hazel/Core/SystemInfo.h"
//#include "Renderer.h"
#include "Hazel/Platform/OpenGL/OpenGLVertexArray.h"

namespace Hazel
{
	VertexArray* VertexArray::Create()
	{
		switch (SystemInfo::GetRenderingAPI())
		{

		case SystemInfo::RenderingAPI::None:
			HZ_CORE_ASSERT(false, "RenderAPI None is not supported!");
			return nullptr;
		case SystemInfo::RenderingAPI::OpenGL:
			return new OpenGLVertexArray();

		default:
			HZ_CORE_ASSERT(false, "RenderAPI is not currently supported!");
			return nullptr;
		}
	}
}