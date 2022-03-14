#pragma once


namespace Hazel
{
	class Time
	{
	public:

		virtual ~Time() = default;

		virtual float GetTime() const = 0;
		
		static Time* Create();
	};

	class DeltaTime
	{
	public:
		DeltaTime(float time = 0.0f)
			:m_Time(time)
		{
		}

		~DeltaTime() = default;
		
		operator float() const { return m_Time; }

		inline float GetSeconds() const { return m_Time; }
		inline float GetMillis() const { return m_Time * 1000.0f; }

	private:
		float m_Time;
	};
}