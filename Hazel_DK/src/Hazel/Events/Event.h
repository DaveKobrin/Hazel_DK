#pragma once
#include "hzpch.h"
#include "Hazel/Core.h"

namespace Hazel {
	// Events in Hazel are currently blocking, meaning that an event must be fully proccessed
	// imediately. In the future it would be better to buffer events into a que and proccess them
	// at an "Event" stage of application update

	//TODO: Build buffered event system

	enum class EventType
	{
		None = 0,
		
		// Window Events
		WindowClose,
		WindowResize,
		WindowFocus,
		WindowLostFocus,
		WindowMoved,
		
		// Application Events
		AppTick,
		AppUpdate,
		AppRender,
		
		// Keyboard Events
		KeyPressed,
		KeyReleased,

		//Mouse Events
		MouseButtonPressed,
		MouseButtonReleased,
		MouseMoved,
		MouseScrolled
	};

	enum EventCategory {
		// fast method to filter events at run time based on bitfield
		// an event may be more than one category ie. EventCategoryInput && EventCategoryKeyboard
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput       = BIT(1),
		EventCategoryKeyboard    = BIT(2),
		EventCategoryMouse       = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

	// siimple macros to help create subclass function overrides
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
							   virtual EventType GetEventType() const override { return GetStaticType(); }\
							   virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class HAZEL_API Event
	{
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category) { return GetCategoryFlags() & category; }
		friend std::ostream& operator<<(std::ostream& os, const Event& e);

	protected:
		bool m_handled = false;
	};


	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;

	public:
		EventDispatcher(Event& event)
			:m_Event(event) {}

		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return (os << e.ToString());
	}
}