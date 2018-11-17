#pragma once

#include <array>
#include <set>
#include <vector>

#include "InputEvent.h"

namespace apryx {

	class Gamepad {
	public:
		enum GamepadButton {
			Up = 0,
			Down,
			Left,
			Right,

			Start,
			Back,

			LeftStick,
			RightStick,

			LeftShoulder,
			RightShoulder,

			A,
			B,
			X,
			Y,

			ButtonCount
		};

		enum GamepadAxis {
			LeftX = 0,
			LeftY,

			RightX,
			RightY,

			LeftTrigger,
			RightTrigger,

			AxisCount
		};
	private:
		std::array<bool, ButtonCount> m_Buttons;
		std::set<GamepadButton> m_ButtonsReleased;
		std::set<GamepadButton> m_ButtonsPressed;

		std::array<float, AxisCount> m_Axes;

		bool m_Connected = false;
	public:
		bool isButtonDown(GamepadButton button) const;
		bool isButtonUp(GamepadButton button) const;
		bool isButtonPressed(GamepadButton button) const;

		float getAxis(GamepadAxis axis) const;

		bool isConnected() const { return m_Connected; };

		void clear();
		void processEvents(const std::vector<InputEvent> &inputs, int index);
	};

}