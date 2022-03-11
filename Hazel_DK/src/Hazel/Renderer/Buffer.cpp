#include "hzpch.h"
#include "Buffer.h"

#include "Hazel/Core/SystemInfo.h"
//#include "Renderer.h"

#include "Hazel/Platform/OpenGL/OpenGLBuffer.h"

namespace Hazel
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (SystemInfo::GetRenderingAPI())
		{

		case SystemInfo::RenderingAPI::None:
			HZ_CORE_ASSERT(false, "RenderAPI None is not supported!");
			return nullptr;
		case SystemInfo::RenderingAPI::OpenGL:
			return new OpenGLVertexBuffer(vertices, size);
		
		default:
			HZ_CORE_ASSERT(false, "RenderAPI is not currently supported!");
			return nullptr;
		}

	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (SystemInfo::GetRenderingAPI())
		{

		case SystemInfo::RenderingAPI::None:
			HZ_CORE_ASSERT(false, "RenderAPI None is not supported!");
			return nullptr;
		case SystemInfo::RenderingAPI::OpenGL:
			return new OpenGLIndexBuffer(indices, count);

		default:
			HZ_CORE_ASSERT(false, "RenderAPI is not currently supported!");
			return nullptr;
		}
	}
}