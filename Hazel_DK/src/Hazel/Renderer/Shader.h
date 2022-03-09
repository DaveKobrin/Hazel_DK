#pragma once
#include <string>

namespace Hazel
{
	class Shader
	{
	public:
		virtual ~Shader() {}

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		static Shader* Create(const std::string& vertSrc, const std::string& fragSrc);

	};
}