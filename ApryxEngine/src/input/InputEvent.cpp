#include "InputEvent.h"

namespace apryx {

	InputEvent::InputEvent() : m_Consumed(false)
	{ }

	std::ostream & operator<<(std::ostream & stream, InputEvent::EventType type)
	{
		switch (type) {
		case InputEvent::EventType::MousePressed: return stream << "MousePressed";
		case InputEvent::EventType::MouseReleased: return stream << "MouseReleased";
		case InputEvent::EventType::MouseMove: return stream << "MouseMove";
		case InputEvent::EventType::MouseDrag: return stream << "MouseDrag";

		case InputEvent::EventType::KeyboardTyped: return stream << "KeyboardTyped";
		case InputEvent::EventType::KeyboardPressed: return stream << "KeyboardPressed";
		case InputEvent::EventType::KeyboardReleased: return stream << "KeyboardReleased";
		}

		return stream;
	}
}