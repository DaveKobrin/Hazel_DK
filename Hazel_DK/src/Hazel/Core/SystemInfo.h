#pragma once


namespace Hazel
{
	class SystemInfo
	{
	public:
		enum class SystemPlatform
		{
			None = 0,
			Windows,
			MacOS,
			Linux,
			Android
		};

		enum class RenderingAPI
		{
			None = 0,
			OpenGL,
			DirectX,
			Vulcan,
			Metal
		};

		inline static void SetSystemPlatform(SystemPlatform platform) { s_SystemPlatform = platform; }
		inline static SystemPlatform GetSystemPlatform() { return s_SystemPlatform; }

		inline static void SetRenderingAPI(RenderingAPI api) { s_RenderingAPI = api; }
		inline static RenderingAPI GetRenderingAPI() { return s_RenderingAPI; }

	private:
		static SystemPlatform s_SystemPlatform;
		static RenderingAPI s_RenderingAPI;
	};

}