#include "Gamepad.h"

namespace apryx {

	bool Gamepad::isButtonDown(GamepadButton button) const
	{
		return m_Buttons[button];
	}

	bool Gamepad::isButtonUp(GamepadButton button) const
	{
		return m_ButtonsReleased.find(button) != m_ButtonsReleased.end();
	}

	bool Gamepad::isButtonPressed(GamepadButton button) const
	{
		return m_ButtonsPressed.find(button) != m_ButtonsPressed.end();
	}

	float Gamepad::getAxis(GamepadAxis axis) const
	{
		return m_Axes[axis];
	}

	void Gamepad::clear()
	{
		m_ButtonsPressed.clear();
		m_ButtonsReleased.clear();
	}

	void Gamepad::processEvents(const std::vector<InputEvent>& inputs, int index)
	{
		for (auto &i : inputs) {

			switch (i.getType()) {
			case InputEvent::GamepadAxisChanged:
			case InputEvent::GamepadButtonPressed:
			case InputEvent::GamepadButtonReleased:
			case InputEvent::GamepadConnected:
			case InputEvent::GamepadDisconnected:
				if(i.getGamepadIndex() != index)
					continue;
			}

			if (i.getType() == InputEvent::GamepadButtonPressed) {
				auto button = i.getGamepadButton();
				m_ButtonsPressed.insert((GamepadButton)button);
				m_Buttons[button] = true;
			}
			if (i.getType() == InputEvent::GamepadButtonReleased) {
				auto button = i.getGamepadButton();
				m_ButtonsReleased.insert((GamepadButton)button);
				m_Buttons[button] = false;
			}
			if (i.getType() == InputEvent::GamepadAxisChanged) {
				auto axis = i.getGamepadAxis();
				m_Axes[axis] = i.getGamepadAxisValue();
			}

			if (i.getType() == InputEvent::GamepadConnected) {
				m_Connected = true;
			}
			if (i.getType() == InputEvent::GamepadDisconnected) {
				m_Connected = false;
			}
		}
	}
}
