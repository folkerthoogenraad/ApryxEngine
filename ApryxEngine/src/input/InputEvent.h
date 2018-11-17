#pragma once
#pragma once

#include <memory>
#include <iostream>

#include "math/Vector2.h"

#define MOUSE_LBUTTON		0x01
#define MOUSE_RBUTTON		0x02
#define MOUSE_MBUTTON		0x04
#define MOUSE_X1BUTTON		0x05
#define MOUSE_X2BUTTON		0x06

#define KEY_TAB				0x09
#define KEY_ENTER			0x0D
#define KEY_ESCAPE			0x1B
#define KEY_SPACE			0x20
#define KEY_BACKSPACE		0x08

#define KEY_ANY_SHIFT		0x10
#define KEY_ANY_CONTROL		0x11

#define KEY_LSHIFT			0xA0
#define KEY_RSHIFT			0xA1
#define KEY_LCONTROL		0xA2
#define KEY_RCONTROL		0xA3

#define KEY_SPACE			0x20
#define KEY_PRIOR			0x21
#define KEY_NEXT			0x22
#define KEY_END				0x23
#define KEY_HOME			0x24
#define KEY_LEFT			0x25
#define KEY_UP				0x26
#define KEY_RIGHT			0x27
#define KEY_DOWN			0x28
#define KEY_SELECT			0x29
#define KEY_PRINT			0x2A
//#define KEY_EXECUTE			0x2B
#define KEY_SNAPSHOT		0x2C
#define KEY_INSERT			0x2D
#define KEY_DELETE			0x2E
#define KEY_HELP			0x2F

#define KEY_NUMPAD0			0x60
#define KEY_NUMPAD1			0x61
#define KEY_NUMPAD2			0x62
#define KEY_NUMPAD3			0x63
#define KEY_NUMPAD4			0x64
#define KEY_NUMPAD5			0x65
#define KEY_NUMPAD6			0x66
#define KEY_NUMPAD7			0x67
#define KEY_NUMPAD8			0x68
#define KEY_NUMPAD9			0x69
#define KEY_MULTIPLY		0x6A
#define KEY_ADD				0x6B
#define KEY_SEPARATOR		0x6C
#define KEY_SUBTRACT		0x6D
#define KEY_DECIMAL			0x6E
#define KEY_DIVIDE			0x6F
#define KEY_F1				0x70
#define KEY_F2				0x71
#define KEY_F3				0x72
#define KEY_F4				0x73
#define KEY_F5				0x74
#define KEY_F6				0x75
#define KEY_F7				0x76
#define KEY_F8				0x77
#define KEY_F9				0x78
#define KEY_F10				0x79
#define KEY_F11				0x7A
#define KEY_F12				0x7B
#define KEY_F13				0x7C
#define KEY_F14				0x7D
#define KEY_F15				0x7E
#define KEY_F16				0x7F
#define KEY_F17				0x80
#define KEY_F18				0x81
#define KEY_F19				0x82
#define KEY_F20				0x83
#define KEY_F21				0x84
#define KEY_F22				0x85
#define KEY_F23				0x86
#define KEY_F24				0x87

#define KEY_0				0x30
#define KEY_1				0x31
#define KEY_2				0x32
#define KEY_3				0x33
#define KEY_4				0x34
#define KEY_5				0x35
#define KEY_6				0x36
#define KEY_7				0x37
#define KEY_8				0x38
#define KEY_9				0x39

#define KEY_A				0x41
#define KEY_B				0x42
#define KEY_C				0x43
#define KEY_D				0x44
#define KEY_E				0x45
#define KEY_F				0x46
#define KEY_G				0x47
#define KEY_H				0x48
#define KEY_I				0x49
#define KEY_J				0x4A
#define KEY_K				0x4B
#define KEY_L				0x4C
#define KEY_M				0x4D
#define KEY_N				0x4E
#define KEY_O				0x4F
#define KEY_P				0x50
#define KEY_Q				0x51
#define KEY_R				0x52
#define KEY_S				0x53
#define KEY_T				0x54
#define KEY_U				0x55
#define KEY_V				0x56
#define KEY_W				0x57
#define KEY_X				0x58
#define KEY_Y				0x59
#define KEY_Z				0x5A

namespace apryx {

	class InputEvent {
	public:
		enum EventType {
			MousePressed = 0,
			MouseReleased,
			MouseMove,
			MouseDrag,
			MouseScroll,

			KeyboardTyped,
			KeyboardPressed,
			KeyboardReleased,

			GamepadButtonPressed,
			GamepadButtonReleased,
			GamepadAxisChanged,
			GamepadConnected,
			GamepadDisconnected,
		};
	public:
		bool m_Consumed = false;

		EventType m_EventType;

		union {
			struct {
				int m_UnicodeKey;
				int m_KeyCode;
			};
			struct {
				int m_MouseButton;
			};
			struct {
				Vector2f m_MouseStartPosition; 
				Vector2f m_MousePosition;
				Vector2f m_MouseDelta;

				Vector2f m_ScrollDirection;
			};
			struct {
				int m_GamepadIndex;

				int m_GamepadButton;
				int m_GamepadAxis;

				float m_GamepadAxisValue;
			};
		};

		bool m_CrtlDown, m_ShiftDown, m_AltDown;
		bool m_Repeat = false;
	public:
		InputEvent();
		~InputEvent() = default;

		bool isConsumed() const { return m_Consumed; }
		void consume() { m_Consumed = true; }

		EventType getType() const { return m_EventType; }

		bool isCrtlDown() const { return m_CrtlDown; };
		bool isShiftDown() const { return m_ShiftDown; };
		bool isAltDown() const { return m_AltDown; };
		bool isModifierDown() const { return isCrtlDown() || isAltDown() || isShiftDown(); };

		bool isRepeated() const { return m_Repeat; }

		bool isMotionEvent() const { return m_EventType == EventType::MouseDrag || m_EventType == EventType::MouseMove; }

		int getKeyCode() const { return m_KeyCode; }
		int getMouseButton() const { return m_MouseButton; }

		Vector2f getMouseStartPosition() const { return m_MouseStartPosition; }
		Vector2f getMousePosition() const { return m_MousePosition; }
		Vector2f getMouseDelta() const { return m_MouseDelta; }

		Vector2f getScrollDirection() const { return m_ScrollDirection; }

		int getGamepadIndex() const { return m_GamepadIndex; }
		int getGamepadButton() const { return m_GamepadButton; }

		int getGamepadAxis() const { return m_GamepadAxis; }
		float getGamepadAxisValue() const { return m_GamepadAxisValue; }

		int getUnicodeKey() { return m_UnicodeKey; }
		bool hasUnicodeKey() { return m_UnicodeKey > 0; }

		operator bool() { return !m_Consumed; }
	};

	std::ostream &operator <<(std::ostream &stream, InputEvent::EventType type);

}