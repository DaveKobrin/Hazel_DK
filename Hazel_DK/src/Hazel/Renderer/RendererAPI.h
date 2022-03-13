#pragma once

#include <glm/glm.hpp>
#include "VertexArray.h"

namespace Hazel
{
	class RendererAPI
	{
	public:

		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;

	};
}
