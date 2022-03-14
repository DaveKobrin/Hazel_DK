#pragma once


namespace Hazel
{
	class Texture
	{
	public:
		virtual uint32_t GetWidth() = 0;
		virtual uint32_t GetHeight() = 0;

		virtual void Bind() = 0;
	};

	class Texture2D : public Texture
	{
		static Ref<Texture2D> Create(const std::string& filepath);
	};
}
